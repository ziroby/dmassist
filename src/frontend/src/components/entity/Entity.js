import React from 'react';

import './Entity.css';

function Entity(props) {
  return (
    <div className="Entity">
        <span className="name">{props.entity.name}</span>
        <span className="abbrevation">{props.entity.abbreviation}</span>
        <span className="entityType">{props.entity.entityType}</span>
        <span className="initRoll">{props.entity.initRoll}</span>
        <span className="hitpoints">{props.entity.hitpoints}</span>
        <span className="subdual">{props.entity.subdual}</span>
        <span className="roundsLeft">{props.entity.roundsLeft}</span>
    </div>
  );
}

export default Entity;
