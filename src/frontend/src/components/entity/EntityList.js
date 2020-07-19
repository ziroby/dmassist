import React from 'react';

import Entity from './Entity'

import './EntityList.css';


var columns = [
    "Name",
    "Abbr",
    "Type",
    "Init",
    "HP",
    "Sub",
    "Rounds",
];

function EntityList(props) {

  var header = columns.map(columnName => <th>{columnName}</th>);

  return (
    <div className="EntityList">
        <table>
            <tr>{header}</tr>
            {props.entities.map(entity => <Entity entity={entity}/>)
            }
        </table>
    </div>
  );
}

export default EntityList;
