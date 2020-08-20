import React from 'react';

import './LoginDialog.css';

class LoginDialog extends React.Component {
  constructor(props) {
    super(props);
    this.state = {value: ''};

    this.handleChange = this.handleChange.bind(this);
    this.handleSubmit = this.handleSubmit.bind(this);
  }

  handleChange(event) {
    this.setState({value: event.target.value});
  }

  handleSubmit(event) {
    this.props.onLogin(this.state.value);
    event.preventDefault();
  }
  render() {
    return <form className="LoginDialog" onSubmit={this.handleSubmit}>
          <label htmlFor="username">User Name:&nbsp;
          <input type="text" id="username" name="username" value={this.state.value} onChange={this.handleChange}/>
          </label>
          <br/>
          <label htmlFor="password">Password:&nbsp;
          <input type="text" placeholder="No Password Needed" id="password" name="password" disabled />
          </label>
          <br/>
          <input type="submit" value="Submit" />
      </form>
  }
}

export default LoginDialog;
