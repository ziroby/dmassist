import React from 'react';
import './Frame.css';
import axios from 'axios'

import EntityList from '../entity/EntityList';
import AddSampleData from '../data/AddSampleData';
import Time from '../counters/Time';
import InitCount from '../counters/InitCount';
import RoundCount from '../counters/RoundCount';
import LoginDialog from '../auth/LoginDialog';

axios.interceptors.response.use(function (response) {
  return response;
}, function (error) {
  console.log("Error: ", error);
  return Promise.reject(error);
});

const baseUrl = `https://serene-harbor-25816.herokuapp.com/`;
// const baseUrl = `http://localhost:8080/`;

class Frame extends React.Component {

  constructor(props) {
    super(props);
    this.state = {};
  }

  getEntities(optionalUsername) {
    const username = (optionalUsername? optionalUsername : this.state.username)
    if (username) {
      console.log("Get entities")
      axios.get(baseUrl + 'users/' + username + '/battles/1')
        //    axios.get(`http://localhost:8081/battles/1`)
        .then(res => {
          console.log(res);
          const newState = { 
            battle: res.data,            
            username: username,
            error: null
          };
          this.setState(newState);
        })
        .catch(error => {
          this.setState({ 'error': error});
        });
    } 
  }

  componentDidMount() {
    this.getEntities();
  }

  populate() {
    axios.post(baseUrl + 'users/' + this.state.username + '/battles/1/populate')
      //    axios.post(`http://localhost:8081/battles/1/populate`)
      .then(res => {
        console.log(res);
        this.getEntities();
      })
  }

  next() {
    axios.post(baseUrl + 'users/' + this.state.username + '/battles/1/next')
      //    axios.post(`http://localhost:8081/battles/1/next`)
      .then(res => {
        console.log(res);
        this.getEntities();
      })
  }

  reset() {
    axios.post(baseUrl + 'users/' + this.state.username + '/battles/1/reset')
      //    axios.post(`http://localhost:8081/battles/1/reset`)
      .then(res => {
        console.log(res);
        this.getEntities();
      })
  }

  login(username) {
    this.setState({
      "username": username
    });
    console.log("login", username); 
    this.getEntities(username);
   
  }

  render() {

    let error = '';
    if (this.state.error) {
      error = <div className="error">
        <h3>Error</h3>
        <p>{this.state.error.message}</p>
        {/* <p>{JSON.stringify(this.state.error, 2)}</p> */}
      </div>
      
    }

    if (!this.state.username) {
      return <div>
        {error}
        <LoginDialog onLogin={(username) => this.login(username)} />
      </div>
    }

    let list;

    if (this.state.battle) {
      if (!this.state.battle.entities.length) {
        list = <AddSampleData onClick={() => this.populate()} />;
      } else {
        list = <EntityList entities={this.state.battle.entities} />;
      }
      return (
        <div className="Frame">
          <div className="group">
            {list}
          </div>
          <Time time={this.state.battle.time} />
          <RoundCount round={this.state.battle.numRounds} />
          <InitCount init={this.state.battle.initCount} />
          <button onClick={() => this.reset()}>Reset</button>
          <button onClick={() => this.next()}>Next</button>
        </div>
      );
    } else {
      return <div>
        {error}
        Loading data</div>
    }
  }
}

export default Frame;
