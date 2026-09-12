///
/// Macondo.ts
///
/// Domain model for turning the raw "señal cruda" coming from the TGMR
/// worker into the smoothed "Macondo" readings shown in the "serie" pane.
///
/// Per the interview (see Entrevista.md): each Macondian sensor is really
/// an array of microsensors (a fixed-but-model-dependent count). A Macondo
/// reading is NOT a plain average: it's the output of a statistical
/// smoothing model that (a) picks a representative value and (b) discards
/// microsensor outliers using a tolerance margin -- the "radio Macondiano
/// de tolerancia". The interview also asks, explicitly, for a processing
/// interface so different statistical models can be swapped freely; that's
/// the `SmoothingModel` type below.
///

// --- The result type -------------------------------------------------------

// One processed "Macondo" reading: a single sensor, in a single batch,
// after smoothing. This is what the "serie" pane visualizes.
export interface MacondoReading {
  batch: number;      // which batch this sensor reading belongs to
  id: string;         // sensor id, e.g. "Y1001" or "L1002"
  value: number;      // the smoothed Macondo reading
  count: number;      // how many microsensors this sensor reported
  outliers: number;   // how many of those were discarded as outliers
}

// A raw sensor sample, parsed from one "señal cruda" line, before smoothing.
interface RawSensorSample {
  batch: number;
  id: string;
  values: number[];   // one reading per microsensor
}

// What a smoothing model hands back: the representative value, plus how
// many microsensor readings it decided to discard.
interface SmoothingResult {
  value: number;
  outliers: number;
}

// --- The processing interface ----------------------------------------------
//
// "Para intercambiar los modelos con agilidad, va a ser util que definan
// una interfaz de procesamiento" -- any statistical model plugs in here:
// microsensor readings + a tolerance radius in, one Macondo value out.
// The rest of the pipeline (parsing, formatting, wiring into the UI) never
// needs to know which model is behind it.
export type SmoothingModel = (values: number[], toleranceRadius: number) => SmoothingResult;

const median = (values: number[]): number => {
  const sorted = [...values].sort((a, b) => a - b);
  const mid = Math.floor(sorted.length / 2);
  return sorted.length % 2 !== 0 ? sorted[mid] : (sorted[mid - 1] + sorted[mid]) / 2;
};

const mean = (values: number[]): number =>
  values.reduce((sum, v) => sum + v, 0) / values.length;

// Default model: the median is the representative value (robust even if a
// couple of microsensors are way off), then the Macondo reading is the mean
// of whatever falls within `toleranceRadius` of it. Falls back to the full
// set if the radius happens to reject every reading.
export const medianTrimmedMean: SmoothingModel = (values, toleranceRadius) => {
  const center = median(values);
  const margin = Math.max(Math.abs(center), 1e-9) * toleranceRadius;
  const inliers = values.filter(v => Math.abs(v - center) <= margin);
  const kept = inliers.length > 0 ? inliers : values;
  return { value: mean(kept), outliers: values.length - kept.length };
};

// A second model, kept alongside the default to show the interface really
// is swappable: same idea, but trims around the mean instead of the median.
export const meanTrimmedMean: SmoothingModel = (values, toleranceRadius) => {
  const center = mean(values);
  const margin = Math.max(Math.abs(center), 1e-9) * toleranceRadius;
  const inliers = values.filter(v => Math.abs(v - center) <= margin);
  const kept = inliers.length > 0 ? inliers : values;
  return { value: mean(kept), outliers: values.length - kept.length };
};

// The interview suggests 5%~10% of typical values; 8% is the midpoint.
export const DEFAULT_TOLERANCE_RADIUS = 0.08;

// --- Parsing the raw signal --------------------------------------------------
//
// The worker's lines look like:
//   "Batch 3:"                              -> batch header
//   "3 Y1002 [ 2.113,1.987,...,1.998 ]"      -> one sensor's microsensors
//   "Macondian starting ..." / etc.          -> status messages (ignored here)

const SENSOR_LINE = /^(\d+)\s+(\S+)\s*\[\s*([^\]]*)\]\s*$/;
const BATCH_LINE = /^Batch\s+\d+:$/;

const parseSensorLine = (line: string): RawSensorSample | null => {
  const match = SENSOR_LINE.exec(line.trim());
  if (!match) return null;
  const [, batchText, id, valuesText] = match;
  const values = valuesText
    .split(',')
    .map(part => Number(part.trim()))
    .filter(v => !Number.isNaN(v));
  if (values.length === 0) return null;
  return { batch: Number(batchText), id, values };
};

// True for the "Batch N:" header lines, so callers can mirror them as-is in
// the processed series (it then reads like a synchronized view of the raw
// signal, as suggested: "inspirados en la visualización de la señal cruda").
export const isBatchHeader = (line: string): boolean => BATCH_LINE.test(line.trim());

// Turns one raw-signal line into a Macondo reading. Returns null for lines
// that carry no sensor data (batch headers, status messages) -- the caller
// decides what, if anything, to show for those.
export const processRawLine = (
  line: string,
  model: SmoothingModel = medianTrimmedMean,
  toleranceRadius: number = DEFAULT_TOLERANCE_RADIUS,
): MacondoReading | null => {
  const sample = parseSensorLine(line);
  if (!sample) return null;
  const { value, outliers } = model(sample.values, toleranceRadius);
  return { batch: sample.batch, id: sample.id, value, count: sample.values.length, outliers };
};

// Renders a MacondoReading the way the raw Monitor renders its own lines, so
// the "serie" pane visually mirrors "señal cruda": same shape, one number
// instead of the whole microarray.
export const formatReading = (r: MacondoReading): string => {
  const tag = r.outliers > 0 ? ` (${r.outliers}/${r.count} outliers)` : '';
  return `${r.batch} ${r.id} => ${r.value.toFixed(3)}${tag}`;
};
