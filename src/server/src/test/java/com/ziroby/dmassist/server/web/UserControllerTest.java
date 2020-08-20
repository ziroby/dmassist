package com.ziroby.dmassist.server.web;

import org.junit.jupiter.api.Test;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.autoconfigure.web.servlet.AutoConfigureMockMvc;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.http.MediaType;
import org.springframework.test.web.servlet.MockMvc;
import org.springframework.test.web.servlet.request.MockMvcRequestBuilders;

import static org.hamcrest.Matchers.*;
import static org.springframework.test.web.servlet.result.MockMvcResultMatchers.content;
import static org.springframework.test.web.servlet.result.MockMvcResultMatchers.status;

@SpringBootTest
@AutoConfigureMockMvc
public class UserControllerTest {

    public static final String EMPTY_BATTLE = "{\"id\":1," +
            "\"initCount\":null," +
            "\"numRounds\":0," +
            "\"time\":\"00:00\"," +
            "\"entities\":[]}";
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
                .andExpect(content().json("{\"userName\":\"Ziroby\",\"battles\":[]}"));
        ;
    }

    @Test
    public void getBattleNonExistentUser() throws Exception {
        mvc.perform(MockMvcRequestBuilders.get("/users/Nonexistent/battles/1").accept(MediaType.APPLICATION_JSON))
                .andExpect(status().isNotFound());
    }

    @Test
    public void getEmptyBattle() throws Exception {
        createUser("test2");
        mvc.perform(MockMvcRequestBuilders.put("/users/test2/battles").accept(MediaType.APPLICATION_JSON))
                .andExpect(status().isOk());
        mvc.perform(MockMvcRequestBuilders.get("/users/test2/battles/1").accept(MediaType.APPLICATION_JSON))
                .andExpect(status().isOk())
                .andExpect(content().json(EMPTY_BATTLE));
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
                .andExpect(content().string(not(equalTo(EMPTY_BATTLE))));

    }

    @Test
    public void startCombat() throws Exception {
        createUser("test4");
        mvc.perform(MockMvcRequestBuilders.put("/users/test4/battles").accept(MediaType.APPLICATION_JSON))
                .andExpect(status().isOk());
        mvc.perform(MockMvcRequestBuilders.post("/users/test4/battles/1/populate").accept(MediaType.APPLICATION_JSON))
                .andExpect(status().isOk());
        mvc.perform(MockMvcRequestBuilders.get("/users/test4/battles/1").accept(MediaType.APPLICATION_JSON))
                .andExpect(status().isOk())
                .andExpect(content().string(not(containsString("\"myTurn\":true"))));
        mvc.perform(MockMvcRequestBuilders.post("/users/test4/battles/1/next").accept(MediaType.APPLICATION_JSON))
                .andExpect(status().isOk());
        mvc.perform(MockMvcRequestBuilders.get("/users/test4/battles/1").accept(MediaType.APPLICATION_JSON))
                .andExpect(status().isOk())
                .andExpect(content().string(containsString("\"myTurn\":true")));

    }

    @Test
    public void resetCombat() throws Exception {
        createUser("test5");
        mvc.perform(MockMvcRequestBuilders.put("/users/test5/battles").accept(MediaType.APPLICATION_JSON))
                .andExpect(status().isOk());
        mvc.perform(MockMvcRequestBuilders.post("/users/test5/battles/1/populate").accept(MediaType.APPLICATION_JSON))
                .andExpect(status().isOk());
        mvc.perform(MockMvcRequestBuilders.get("/users/test5/battles/1").accept(MediaType.APPLICATION_JSON))
                .andExpect(status().isOk())
                .andExpect(content().string(not(containsString("\"myTurn\":true"))));
        mvc.perform(MockMvcRequestBuilders.post("/users/test5/battles/1/next").accept(MediaType.APPLICATION_JSON))
                .andExpect(status().isOk());
        mvc.perform(MockMvcRequestBuilders.get("/users/test5/battles/1").accept(MediaType.APPLICATION_JSON))
                .andExpect(status().isOk())
                .andExpect(content().string(containsString("\"myTurn\":true")));
        mvc.perform(MockMvcRequestBuilders.post("/users/test5/battles/1/reset").accept(MediaType.APPLICATION_JSON))
                .andExpect(status().isOk());
        mvc.perform(MockMvcRequestBuilders.get("/users/test5/battles/1").accept(MediaType.APPLICATION_JSON))
                .andExpect(status().isOk())
                .andExpect(content().string(not(containsString("\"myTurn\":true"))));

    }

    private void createUser(String user) throws Exception {
        mvc.perform(MockMvcRequestBuilders.put("/users/" + user).accept(MediaType.APPLICATION_JSON))
                .andExpect(status().isOk());
    }
}