import React from 'react';

import Frame from './components/frame/Frame';

import './App.css';

const state = {
    entities: [{
        name: "Ziroby",
        abbreviation: "Z",
        type: "PC",
        init: "+8",
        hp: "7d4",
        sub: null,
        rounds: null
    },{
        name: "Goblin 1",
        abbreviation: "G1",
        type: "M",
        init: "+2",
        hp: "1d6",
        sub: null,
        rounds: null
    }]
};

function App() {
  return (
    <div className="App">
      <header className="App-header">
        DM Assist
      </header>
      <Frame state={state}/>
    </div>
  );
}

export default App;
