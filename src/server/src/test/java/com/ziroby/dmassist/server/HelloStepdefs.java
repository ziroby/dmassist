package com.ziroby.dmassist.server;

import io.cucumber.java8.En;
import org.springframework.http.ResponseEntity;

import static org.assertj.core.api.Assertions.assertThat;

public class HelloStepdefs extends SpringCucumberIntegrationTests implements En {

    ResponseEntity<String> result;
    public HelloStepdefs() {
        When("^the client calls /hi$", () -> {
            result = restTemplate
                    .getForEntity(dmassistEndpoint() + "hi", String.class);

        });
        Then("^the client receives status code of (\\d+)$", (Integer expectedStatusCode) -> {
            assertThat(result.getStatusCode().value()).isEqualTo(expectedStatusCode);
        });
        And("^the client receives a result of \"([^\"]*)\"$", (String expectedResult) -> {
            assertThat(result.getBody()).isEqualTo(expectedResult);
        });
    }
}
