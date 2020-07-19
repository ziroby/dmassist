import React from 'react';

import './Entity.css';

function Entity(props) {
  return (
    <tr className="Entity">
        <td>{props.entity.name}</td>
        <td>{props.entity.abbreviation}</td>
        <td>{props.entity.type}</td>
        <td>{props.entity.init}</td>
        <td>{props.entity.hp}</td>
        <td>{props.entity.subdual}</td>
        <td>{props.entity.rounds}</td>
    </tr>
  );
}

export default Entity;
