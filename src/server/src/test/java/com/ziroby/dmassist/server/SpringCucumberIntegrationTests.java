package com.ziroby.dmassist.server;

import io.cucumber.spring.CucumberContextConfiguration;
import org.junit.Ignore;
import org.junit.runner.RunWith;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.boot.web.server.LocalServerPort;
import org.springframework.test.context.junit4.SpringRunner;
import org.springframework.web.client.RestTemplate;

@CucumberContextConfiguration
@RunWith(SpringRunner.class)
@SpringBootTest(webEnvironment = SpringBootTest.WebEnvironment.RANDOM_PORT)
@Ignore
public class SpringCucumberIntegrationTests {
    private final String SERVER_URL = "http://localhost";
    private final String DMASSIST_ENDPOINT = "/";
    protected RestTemplate restTemplate;
    @LocalServerPort
    protected int port;
    public SpringCucumberIntegrationTests() {
        this.restTemplate = new RestTemplate();
    }
    protected String dmassistEndpoint() {
        return SERVER_URL + ":" + port + DMASSIST_ENDPOINT;
    }
    int put(String something) {
        return restTemplate
                .postForEntity(dmassistEndpoint(), something, Void.class)
                .getStatusCodeValue();
    }
    String getContents() {
        return restTemplate
                .getForEntity(dmassistEndpoint(), String.class)
                .getBody();
    }
    void clean() {
        restTemplate.delete(dmassistEndpoint());
    }
}