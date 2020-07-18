import React from 'react';
import './Frame.css';

import EntityList from '../entity/EntityList';

function Frame() {
  return (
    <div className="Frame">
      <header className="Frame-header">
        <EntityList />
      </header>
    </div>
  );
}

export default Frame;
