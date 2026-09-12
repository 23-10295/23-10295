///
/// Image
///
/// Renders artwork (1920x1080 stills, screenshots, etc.) inside whatever
/// pane hosts it: full screen ("Image" view) or side-by-side with the
/// Monitor ("Raw" view). The source images are much bigger than any pane,
/// so this component -- not the caller -- is responsible for scaling them
/// down, centering them, and giving them a frame instead of spilling the
/// native resolution over the rest of the interface.

import { useEffect, useState } from "react";

interface Props {
  image: string;
};

const Image = ({ image }: Props) => {
  const src = new URL(`../images/${image}`, import.meta.url).href;
  const [loaded, setLoaded] = useState(false);

  // Re-arm the fade-in whenever a different image is requested.
  useEffect(() => setLoaded(false), [image]);

  return (
    <div className="image-stage">
      <img
        key={image}
        className={`image-frame${loaded ? " is-loaded" : ""}`}
        src={src}
        alt={image}
        onLoad={() => setLoaded(true)}
      />
      <span className="image-caption">{image}</span>
    </div>
  );
};

export default Image;
