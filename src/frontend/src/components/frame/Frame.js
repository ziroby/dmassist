import React from 'react';
import './Frame.css';
import axios from 'axios'

import EntityList from '../entity/EntityList';
import AddSampleData from '../data/AddSampleData';
import Time from '../counters/Time';
import InitCount from '../counters/InitCount';
import RoundCount from '../counters/RoundCount';

class Frame extends React.Component {
  constructor(props) {
    super(props);
    this.state = {
        entities: []
    };
  }

  getEntities() {
    axios.get(`https://serene-harbor-25816.herokuapp.com/battles/1`)
//    axios.get(`http://localhost:8081/battles/1`)
         .then(res => {
      console.log(res);
      const entities = res.data;
      this.setState(entities);
    })
  }

  componentDidMount() {
    this.getEntities();
  }

  populate() {
    axios.post(`https://serene-harbor-25816.herokuapp.com/battles/1/populate`)
//    axios.post(`http://localhost:8081/battles/1/populate`)
    .then(res => {
      console.log(res);
      this.getEntities();
    })
  }

  next() {
    axios.post(`https://serene-harbor-25816.herokuapp.com/battles/1/next`)
//    axios.post(`http://localhost:8081/battles/1/next`)
    .then(res => {
      console.log(res);
      this.getEntities();
    })
  }

  reset() {
    axios.post(`https://serene-harbor-25816.herokuapp.com/battles/1/reset`)
//    axios.post(`http://localhost:8081/battles/1/reset`)
    .then(res => {
      console.log(res);
      this.getEntities();
    })
  }

  render() {
    let list;

    if (!this.state.entities.length) {
      list = <AddSampleData onClick={() => this.populate()}/>;
    } else {
      list = <EntityList entities={this.state.entities}/>;
    }
    return (
    <div className="Frame">
      <div className="group">
        {list}
      </div>
      <Time time={this.state.time}/>
      <RoundCount round={this.state.numRounds}/>
      <InitCount init={this.state.initCount}/>
      <button onClick={() => this.reset()}>Reset</button>
      <button onClick={() => this.next()}>Next</button>
    </div>
    );
  }
}

export default Frame;
