import React from 'react';

import './RoundCount.css';

function RoundCount(props) {
  return (
    <div className="RoundCount">
        round:&nbsp;{props.round}
    </div>
  );
}

export default RoundCount;
