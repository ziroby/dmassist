package com.ziroby.dmassist.server.web;

import org.junit.jupiter.api.Test;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.autoconfigure.web.servlet.AutoConfigureMockMvc;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.http.MediaType;
import org.springframework.test.web.servlet.MockMvc;
import org.springframework.test.web.servlet.request.MockMvcRequestBuilders;

import static org.hamcrest.Matchers.equalTo;
import static org.hamcrest.Matchers.not;
import static org.springframework.test.web.servlet.result.MockMvcResultMatchers.content;
import static org.springframework.test.web.servlet.result.MockMvcResultMatchers.status;

@SpringBootTest
@AutoConfigureMockMvc
public class UserControllerTest {

    @Autowired
    private MockMvc mvc;

    @Test
    public void getNonExistent() throws Exception {
        mvc.perform(MockMvcRequestBuilders.get("//users/Nonexistent").accept(MediaType.APPLICATION_JSON))
                .andExpect(status().isNotFound());
    }

    @Test
    public void getExisting() throws Exception {
        createUser("Ziroby");
        mvc.perform(MockMvcRequestBuilders.get("/users/Ziroby").accept(MediaType.APPLICATION_JSON))
                .andExpect(status().isOk())
                .andExpect(content().string(equalTo("{\"userName\":\"Ziroby\",\"battles\":[]}")));
        ;
    }

    @Test
    public void getEmptyBattle() throws Exception {
        createUser("test2");
        mvc.perform(MockMvcRequestBuilders.put("/users/test2/battles").accept(MediaType.APPLICATION_JSON))
                .andExpect(status().isOk());
        mvc.perform(MockMvcRequestBuilders.get("/users/test2/battles/1").accept(MediaType.APPLICATION_JSON))
                .andExpect(status().isOk())
                .andExpect(content().string(equalTo(
                        "{\"id\":1," +
                                "\"initCount\":null," +
                                "\"numRounds\":0," +
                                "\"time\":\"00:00\"," +
                                "\"entities\":[]}")));
    }

    @Test
    public void populateBattle() throws Exception {
        createUser("test3");
        mvc.perform(MockMvcRequestBuilders.put("/users/test3/battles").accept(MediaType.APPLICATION_JSON))
                .andExpect(status().isOk());
        mvc.perform(MockMvcRequestBuilders.post("/users/test3/battles/1/populate").accept(MediaType.APPLICATION_JSON))
                .andExpect(status().isOk());
        mvc.perform(MockMvcRequestBuilders.get("/users/test3/battles/1").accept(MediaType.APPLICATION_JSON))
                .andExpect(status().isOk())
                .andExpect(content().string(not(equalTo(
                        "{\"id\":1," +
                                "\"initCount\":null," +
                                "\"numRounds\":0," +
                                "\"time\":\"00:00\"," +
                                "\"entities\":[]}"))));

    }

    private void createUser(String user) throws Exception {
        mvc.perform(MockMvcRequestBuilders.put("/users/" + user).accept(MediaType.APPLICATION_JSON))
                .andExpect(status().isOk());
    }
}