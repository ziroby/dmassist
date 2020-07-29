package com.ziroby.dmassist.server.web;

import com.ziroby.dmassist.model.EnhancedEntity;
import com.ziroby.dmassist.model.EnhancedEntityList;
import com.ziroby.dmassist.server.model.JsonEntity;
import com.ziroby.dmassist.server.model.Battle;
import com.ziroby.dmassist.server.repo.UserRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

import java.util.Collection;
import java.util.List;
import java.util.stream.Collectors;

@RestController
public class BattleController {

    @Autowired
    private UserRepository userRepository;

    private final EnhancedEntityList entityList = new EnhancedEntityList();

    @RequestMapping("/users/{userName}/battles/{battleNum}/entities")
    @ResponseBody
    public List<JsonEntity> entities(@PathVariable String userName, @PathVariable String battleNum) {
        userRepository.getBattle(userName, battleNum);
        Collection<EnhancedEntity> entities = entityList.getEnhancedEntities();
        return entities.stream()
                .map(JsonEntity::new)
                .collect(Collectors.toList());
    }

    @PostMapping("/battles/1/populate")
    public void populate() {
        entityList.addSampleData();
    }

    @PostMapping("/battles/1/next")
    public void next() {
        entityList.gotoNextInitCount();
    }

    @PostMapping("/battles/1/reset")
    public void reset() {
        entityList.resetNumRounds();
    }

    @RequestMapping("/battles/1")
    @ResponseBody
    public Battle getBattle() {
        Battle battle = new Battle(entityList);
        return battle;
    }
}