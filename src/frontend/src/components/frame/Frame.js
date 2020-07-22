import React from 'react';
import './Frame.css';
import axios from 'axios'

import EntityList from '../entity/EntityList';
import AddSampleData from '../data/AddSampleData'

class Frame extends React.Component {
  constructor(props) {
    super(props);
    this.state = {
        entities: []
    };
  }

  getEntities() {
    axios.get(`https://serene-harbor-25816.herokuapp.com/battles/1/entities`)
//    axios.get(`http://localhost:8081/battles/1/entities`)
         .then(res => {
      console.log(res);
      const entities = res.data;
      this.setState({ entities: entities });
    })
  }

  componentDidMount() {
    this.getEntities();
  }

  populate() {
    axios.post(`https://serene-harbor-25816.herokuapp.com/battles/1/populate`)
//    axios.get(`http://localhost:8081/battles/1/entities`)
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
      {list}
    </div>
    );
  }
}

export default Frame;
