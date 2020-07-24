import React from 'react';

import Entity from './Entity'

import './Entities.css';

function Entities(props) {
  return props.entities.map(entity => <Entity entity={entity} key={entity.abbreviation}/>)
}

export default Entities;
