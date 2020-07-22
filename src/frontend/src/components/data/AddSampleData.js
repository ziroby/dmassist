import React from 'react';

import './AddSampleData.css';

function AddSampleData(props) {
  return (
    <button className="AddSampleData" onClick={props.onClick}>
      Add Sample Data
    </button>
  );
}

export default AddSampleData;
