///
/// ToolBar
///

interface Props {
  start: () => void;
  reset: () => void;
  uxColor: (mode: number) => string;
  setUX: (mode: number) => void;
  error?: string; 
};

const ToolBar = (props: Props) => {
  // A view button gets the filled "pill" treatment when it's the active one,
  // so the current mode reads as a real toggle state, not just a text tint.
  const viewClass = (mode: number) => `input-group-text${props.uxColor(mode) === "Yellow" ? " tb-active" : ""}`;

  return (
    <div className="app-toolbar mt-2" data-bs-theme="dark">
      <div className="input-group">
        { props.error && <span className="toolbar-error">{props.error}</span> }
        <button className="input-group-text" title={"Start the Macondian Reactor"} style={{ color: "var(--mac-ok)" }} onClick={props.start}>Start Macondian</button>
        <text className="input-group-text flex-fill"/>
        <button className={viewClass(0)} title={"Raw: ..."  } style={{ color: props.uxColor(0) }} onClick={props.setUX.bind(null, 0)}>Raw</button>
        <button className={viewClass(1)} title={"Test: ..." } style={{ color: props.uxColor(1) }} onClick={props.setUX.bind(null, 1)}>Test</button>
        <button className={viewClass(2)} title={"Chart: ..."} style={{ color: props.uxColor(2) }} onClick={props.setUX.bind(null, 2)}>Chart</button>
        <button className={viewClass(3)} title={"Image: ..."} style={{ color: props.uxColor(3) }} onClick={props.setUX.bind(null, 3)}>Image</button>
        <button className={viewClass(4)} title={"List: ..." } style={{ color: props.uxColor(4) }} onClick={props.setUX.bind(null, 4)}>List</button>
        <text className="input-group-text flex-fill"/>
        <button className="input-group-text" title={"Reset the Macondian Reactor"} style={{ color: "var(--mac-warn)" }} onClick={props.reset}>Reset Macondian</button>
      </div>
    </div>
  )
};

export default ToolBar;
