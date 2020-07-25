import React from 'react';

import './InitCount.css';

function InitCount(props) {
  return (
    <div className="InitCount">
        init: &nbsp;{props.init}
    </div>
  );
}

export default InitCount;
