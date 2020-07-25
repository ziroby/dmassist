package com.ziroby.dmassist.server;

import com.ziroby.dmassist.gwtable.model.Entity;
import com.ziroby.dmassist.gwtable.model.EntityList;
import com.ziroby.dmassist.model.EnhancedEntity;
import com.ziroby.dmassist.model.EnhancedEntityList;
import com.ziroby.dmassist.server.model.JsonEntity;
import com.ziroby.dmassist.server.model.JsonEntityList;
import org.springframework.beans.BeanUtils;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.ResponseBody;
import org.springframework.web.bind.annotation.RestController;

import java.util.Collection;
import java.util.List;
import java.util.stream.Collectors;

@RestController
public class BattleController {

    private EnhancedEntityList entityList = new EnhancedEntityList();

    @RequestMapping("/battles/1/entities")
    @ResponseBody
    public List<JsonEntity> entities() {
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
    public JsonEntityList getBattle() {
        JsonEntityList jsonEntityList = new JsonEntityList(entityList);
        return jsonEntityList;
    }
}