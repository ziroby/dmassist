import React from 'react';

import './Time.css';

function Time(props) {
  return (
    <div className="Time">
        {props.time}
    </div>
  );
}

export default Time;
