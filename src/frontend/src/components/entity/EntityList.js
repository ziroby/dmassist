import React from 'react';

import Entities from './Entities'

import './EntityList.css';

function EntityList(props) {

  return (
    <div className="EntityList">
        <Entities entities={props.entities}/>
    </div>
  );
}

export default EntityList;
