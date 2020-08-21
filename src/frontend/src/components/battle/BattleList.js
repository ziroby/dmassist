import React from 'react';
import Battle from './Battle';

import './BattleList.css';

function BattleList(props) {
  return (props.battles.map(battle => <Battle battle={battle} key={battle.id} onClick={props.onSelect}/>));
}

export default BattleList;
