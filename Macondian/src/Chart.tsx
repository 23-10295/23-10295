///
/// Chart
///
/// Visualizes the processing of the system: one line per sensor, showing
/// how its smoothed Macondo reading (see src/Macondo.ts) evolves batch
/// after batch. Outlier-heavy readings are flagged with a ring marker so
/// the *quality* of the smoothing -- not just its output -- is visible.
///

import { useMemo, useState } from 'react';
import type { MacondoReading } from './Macondo';

interface Props {
  readings: MacondoReading[];
}

// Fixed drawing surface; the <svg> scales to its container via viewBox.
const WIDTH = 640;
const HEIGHT = 360;
const MARGIN = { top: 16, right: 16, bottom: 34, left: 46 };
const PLOT_W = WIDTH - MARGIN.left - MARGIN.right;
const PLOT_H = HEIGHT - MARGIN.top - MARGIN.bottom;

// One color per sensor, cycling if there happen to be more sensors than colors.
const PALETTE = [
  '#8a7bff', '#47bfff', '#3ddc84', '#ff9f5a',
  '#ff5f56', '#f5d90a', '#00d1b2', '#ff6ec7',
];

interface Series {
  id: string;
  color: string;
  points: MacondoReading[];
}

// "Nice" round numbers for axis ticks (1/2/5 x 10^n family).
const niceStep = (roughStep: number): number => {
  if (roughStep <= 0) return 1;
  const magnitude = Math.pow(10, Math.floor(Math.log10(roughStep)));
  const residual = roughStep / magnitude;
  const step = residual > 5 ? 10 : residual > 2 ? 5 : residual > 1 ? 2 : 1;
  return step * magnitude;
};

const Chart = ({ readings }: Props) => {
  const [hover, setHover] = useState<MacondoReading | null>(null);

  const { series, batches, valueMin, valueMax, totalOutliers } = useMemo(() => {
    const byId = new Map<string, MacondoReading[]>();
    let outliers = 0;
    for (const r of readings) {
      const bucket = byId.get(r.id);
      if (bucket) bucket.push(r); else byId.set(r.id, [r]);
      outliers += r.outliers;
    }
    const series: Series[] = [...byId.entries()].map(([id, points], i) => ({
      id,
      color: PALETTE[i % PALETTE.length],
      points: [...points].sort((a, b) => a.batch - b.batch),
    }));
    const batches = [...new Set(readings.map(r => r.batch))].sort((a, b) => a - b);
    const values = readings.map(r => r.value);
    const valueMin = values.length ? Math.min(...values) : 0;
    const valueMax = values.length ? Math.max(...values) : 1;
    return { series, batches, valueMin, valueMax, totalOutliers: outliers };
  }, [readings]);

  if (readings.length === 0) {
    return (
      <>
        <h3>procesamiento</h3>
        <div className="chart-fill pane-fill chart-empty">
          Esperando lecturas del Macondian ...
        </div>
      </>
    );
  }

  const batchMin = batches[0];
  const batchMax = batches[batches.length - 1];
  const xSpan = Math.max(batchMax - batchMin, 1);

  // Pad the value axis so lines never touch the plot edges.
  const rawPad = (valueMax - valueMin) * 0.12 || Math.max(Math.abs(valueMax), 1) * 0.1;
  const yMin = valueMin - rawPad;
  const yMax = valueMax + rawPad;
  const ySpan = Math.max(yMax - yMin, 1e-9);

  const scaleX = (batch: number) => MARGIN.left + ((batch - batchMin) / xSpan) * PLOT_W;
  const scaleY = (value: number) => MARGIN.top + PLOT_H - ((value - yMin) / ySpan) * PLOT_H;

  const yStep = niceStep(ySpan / 4);
  const yTicks: number[] = [];
  for (let v = Math.ceil(yMin / yStep) * yStep; v <= yMax; v += yStep) yTicks.push(v);

  // Thin out X ticks so labels don't collide when there are many batches.
  const xTickEvery = Math.max(1, Math.ceil(batches.length / 10));
  const xTicks = batches.filter((_, i) => i % xTickEvery === 0 || i === batches.length - 1);

  return (
    <>
      <h3>procesamiento</h3>
      <div className="chart-fill pane-fill">
        <svg
          viewBox={`0 0 ${WIDTH} ${HEIGHT}`}
          preserveAspectRatio="xMidYMid meet"
          className="chart-svg"
          role="img"
          aria-label="Gráfica del procesamiento del sistema Macondian"
        >
          {/* horizontal gridlines + Y labels */}
          {yTicks.map(v => (
            <g key={`y-${v}`}>
              <line
                x1={MARGIN.left} x2={WIDTH - MARGIN.right}
                y1={scaleY(v)} y2={scaleY(v)}
                className="chart-grid"
              />
              <text x={MARGIN.left - 8} y={scaleY(v)} className="chart-axis-label" textAnchor="end" dominantBaseline="middle">
                {v.toFixed(2)}
              </text>
            </g>
          ))}

          {/* X labels */}
          {xTicks.map(b => (
            <text
              key={`x-${b}`}
              x={scaleX(b)}
              y={HEIGHT - MARGIN.bottom + 18}
              className="chart-axis-label"
              textAnchor="middle"
            >
              {b}
            </text>
          ))}
          <text
            x={MARGIN.left + PLOT_W / 2}
            y={HEIGHT - 4}
            className="chart-axis-title"
            textAnchor="middle"
          >
            Batch
          </text>

          {/* plot axes */}
          <line x1={MARGIN.left} x2={MARGIN.left} y1={MARGIN.top} y2={MARGIN.top + PLOT_H} className="chart-axis" />
          <line x1={MARGIN.left} x2={WIDTH - MARGIN.right} y1={MARGIN.top + PLOT_H} y2={MARGIN.top + PLOT_H} className="chart-axis" />

          {/* one line + markers per sensor */}
          {series.map(s => (
            <g key={s.id}>
              <polyline
                fill="none"
                stroke={s.color}
                strokeWidth={2}
                strokeLinejoin="round"
                strokeLinecap="round"
                points={s.points.map(p => `${scaleX(p.batch)},${scaleY(p.value)}`).join(' ')}
              />
              {s.points.map(p => (
                <circle
                  key={`${s.id}-${p.batch}`}
                  cx={scaleX(p.batch)}
                  cy={scaleY(p.value)}
                  r={p.outliers > 0 ? 5 : 3}
                  fill={p.outliers > 0 ? 'var(--mac-panel)' : s.color}
                  stroke={p.outliers > 0 ? 'var(--mac-danger)' : 'none'}
                  strokeWidth={p.outliers > 0 ? 2 : 0}
                  className="chart-point"
                  onMouseEnter={() => setHover(p)}
                  onMouseLeave={() => setHover(prev => (prev === p ? null : prev))}
                >
                  <title>
                    {`Batch ${p.batch} · ${p.id} = ${p.value.toFixed(3)}` +
                      (p.outliers > 0 ? ` (${p.outliers}/${p.count} outliers)` : ` (${p.count} sensores)`)}
                  </title>
                </circle>
              ))}
            </g>
          ))}
        </svg>
      </div>

      <div className="chart-legend">
        {series.map(s => (
          <span key={s.id} className="chart-legend-item">
            <span className="chart-legend-swatch" style={{ backgroundColor: s.color }} />
            {s.id}
          </span>
        ))}
        <span className="chart-legend-item chart-legend-stat">
          {batches.length} batch{batches.length !== 1 ? 'es' : ''} · {readings.length} lecturas · {totalOutliers} outliers
        </span>
        {hover && (
          <span className="chart-legend-item chart-legend-hover">
            {hover.id} @ batch {hover.batch}: <b>{hover.value.toFixed(3)}</b>
            {hover.outliers > 0 && ` (${hover.outliers}/${hover.count} outliers)`}
          </span>
        )}
      </div>
    </>
  );
};

export default Chart;
