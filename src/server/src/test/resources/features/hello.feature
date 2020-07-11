Feature: It says hello
  Scenario: Client makes call to hello endpoint
    When the client calls /hi
    Then the client receives status code of 200
    And the client receives a result of "Greetings from Spring Boot!"

