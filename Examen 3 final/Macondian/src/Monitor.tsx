///
/// Monitor: read-only, scrollable view of session history.
///

import { useEffect, useRef } from 'react';

interface Props {
  title: string;
  log: string[];
}

const Monitor = ({ title, log }: Props) => {
  const ref = useRef<HTMLTextAreaElement>(null);

  // Keep the latest entry in view; users can still scroll up freely.
  useEffect(() => {
      const el = ref.current;
      if (el) {
          el.scrollTop = el.scrollHeight;
      }
  }, [history]);

  return (
      <>
        <h3>{title}</h3>
        <textarea
          ref={ref}
          readOnly
          spellCheck={false}
          className="pane-fill"
          value={log.join('\n')}
          style={{
              textAlign: 'left',
              color: 'var(--mac-term-fg)',
              backgroundColor: 'var(--mac-term-bg)',
              resize: 'none',
              fontFamily: 'consolas',
          }}
        />
      </>
  );
};

export default Monitor;
