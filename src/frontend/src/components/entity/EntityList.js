import React from 'react';

import Entity from './Entity'
import Entity2 from './Entity2'

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

function EntityList() {

  var header = columns.map(columnName => <th>{columnName}</th>);

  return (
    <div className="EntityList">
        <table>
            <tr>{header}</tr>

            <Entity/>
            <Entity2/>
        </table>
    </div>
  );
}

export default EntityList;
