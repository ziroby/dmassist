package com.ziroby.dmassist.server.web;

import com.ziroby.dmassist.server.model.Battle;
import com.ziroby.dmassist.server.model.JsonEntity;
import com.ziroby.dmassist.server.repo.UserRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@RestController
public class BattleController {

    @Autowired
    private UserRepository userRepository;

    @RequestMapping("/users/{userName}/battles/{battleNum}/entities")
    @ResponseBody
    public List<JsonEntity> entities(@PathVariable String userName, @PathVariable String battleNum) {
        Battle battle = userRepository.getBattle(userName, battleNum);
        return battle.getEntitiesAsList();
    }

    @PostMapping("/users/{userName}/battles/{battleNum}/populate")
    public void populate(@PathVariable String userName, @PathVariable String battleNum) {
        Battle battle = userRepository.getBattle(userName, battleNum);
        battle.addSampleData();
    }

    @GetMapping("/users/{userName}/battles/{battleNum}")
    public Battle getBattle(@PathVariable String userName, @PathVariable String battleNum) {
        return userRepository.getBattle(userName, battleNum);
    }

    @PostMapping("/users/{userName}/battles/{battleNum}/next")
    public void next(@PathVariable String userName, @PathVariable String battleNum) {
        Battle battle = userRepository.getBattle(userName, battleNum);
        battle.gotoNextInitCount();
    }

    @PostMapping("/users/{userName}/battles/{battleNum}/reset")
    public void reset(@PathVariable String userName, @PathVariable String battleNum) {
        Battle battle = userRepository.getBattle(userName, battleNum);
        battle.resetNumRounds();
    }
}