import React from 'react';

import './Battle.css';

function Battle(props) {
    const name = (props.name? props.name : "Battle #" + props.battle.id);
  return (      
    <div className= "Battle" onClick={() => props.onClick(props.battle)}>
        <span className="name">{name}</span>
        <span className="id">{props.battle.id}</span>
        <span className="time">{props.battle.time}</span>
        <span className="initCount">{props.battle.initCount}</span>
        <span className="numEntities">{props.battle.entities.length}</span>
    </div>
  );
}

export default Battle;