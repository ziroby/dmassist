import React from 'react';
import './Frame.css';

import EntityList from '../entity/EntityList';

function Frame(props) {
  return (
    <div className="Frame">
      <header className="Frame-header">
        <EntityList entities={props.state.entities}/>
      </header>
    </div>
  );
}

export default Frame;
