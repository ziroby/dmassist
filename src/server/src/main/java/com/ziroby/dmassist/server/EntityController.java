package com.ziroby.dmassist.server;

import com.ziroby.dmassist.gwtable.model.Entity;
import com.ziroby.dmassist.gwtable.model.EntityList;
import com.ziroby.dmassist.model.EntityListImpl;
import com.ziroby.dmassist.server.model.JsonEntity;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.ResponseBody;
import org.springframework.web.bind.annotation.RestController;

import java.util.Arrays;
import java.util.Collection;
import java.util.Collections;
import java.util.List;

@RestController
public class EntityController {

    private EntityList entityList = new EntityListImpl();

    @RequestMapping("/battles/1/entities")
    @ResponseBody
    public List<JsonEntity> index() {
        Collection<Entity> entities = entityList.getEntities();
        entities.stream().map(entity -> new JsonEntity(entity));


        return Arrays.asList(JsonEntity.builder().name("ziroby").build());
    }

}