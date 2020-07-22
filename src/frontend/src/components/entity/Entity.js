import React from 'react';

import './Entity.css';

function Entity(props) {
  return (
    <tr className="Entity">
        <td>{props.entity.name}</td>
        <td>{props.entity.abbreviation}</td>
        <td>{props.entity.entityType}</td>
        <td>{props.entity.initRoll}</td>
        <td>{props.entity.hitpoints}</td>
        <td>{props.entity.subdual}</td>
        <td>{props.entity.roundsLeft}</td>
    </tr>
  );
}

export default Entity;
