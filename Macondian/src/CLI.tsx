///
/// CLI.tsx
///

import { SubmitEvent } from 'react';

interface Props {
  req: (event: SubmitEvent<HTMLFormElement>) => void;
  ref: React.RefObject<HTMLInputElement | null>;
};

const CLI = (props: Props) => {
  return (
  <form className="cli-form" onSubmit={props.req}>
    <input className="cli-command" style={{ color: "var(--mac-term-fg)", backgroundColor: "var(--mac-term-bg)" }} ref={props.ref} />
    <input className="cli-submit" style={{ color: "var(--mac-ok)", backgroundColor: "#060606" }} type="submit" value=">>>" />
  </form>
  );
};

export default CLI;
