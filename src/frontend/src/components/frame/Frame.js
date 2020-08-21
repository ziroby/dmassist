import React from 'react';
import './Frame.css';
import axios from 'axios'

import EntityList from '../entity/EntityList';
import AddSampleData from '../data/AddSampleData';
import Time from '../counters/Time';
import InitCount from '../counters/InitCount';
import RoundCount from '../counters/RoundCount';
import LoginDialog from '../auth/LoginDialog';
import BattleList from '../battle/BattleList';

axios.interceptors.response.use(function (response) {
  return response;
}, function (error) {
  console.log("Error: ", error);
  return Promise.reject(error);
});

// const baseUrl = `https://serene-harbor-25816.herokuapp.com/`;
const baseUrl = `http://localhost:8080/`;

class Frame extends React.Component {

  constructor(props) {
    super(props);
    this.state = {};
  }

  getEntities(optionalUsername) {
    if (!this.state.battle) {
      this.getBattles();
    } else {
      const username = (optionalUsername ? optionalUsername : this.state.username)
      if (username) {
        console.log("Get entities")
        axios.get(baseUrl + 'users/' + username + '/battles/1')
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
            this.setState({ 'error': error });
          });
      }
    }
  }

  getBattles() {
    if (this.state.username && !this.state.battles) {
      console.log("Get battles")
      axios.get(baseUrl + 'users/' + this.state.username)
        .then(res => {
          console.log(res);
          const newState = {
            battles: res.data.battles,
            error: null
          };
          this.setState(newState);
        })
        .catch(error => {
          this.setState({ 
            'error': error,
            'username': null
          });
        });
    }
  }

  componentDidMount() {
    // this.getEntities();
  }

  componentDidUpdate() {
    this.getBattles();
  }

  postAction(action) {
    axios.post(baseUrl + 'users/' + this.state.username + '/battles/1/' + action)
      .then(res => {
        console.log(res);
        this.getEntities();
      })
      .catch(error => {
        this.setState({ 'error': error });
      });
  }

  populate() {
    this.postAction('populate');
  }

  next() {
    this.postAction('next');
  }

  reset() {
    this.postAction('reset');
  }

  login(username) {
    this.setState({
      "username": username
    });
    this.getEntities(username);

  }

  setBattle(battle) {
    this.setState({
      "battle": battle
    });
    console.log("battle", battle);    
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

  if (!this.state.battleId && this.state.battles && !this.state.battle) {
      return <BattleList battles={this.state.battles} onSelect={(battle => this.setBattle(battle))}/>
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
          {error}
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
