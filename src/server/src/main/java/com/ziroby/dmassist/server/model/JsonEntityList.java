package com.ziroby.dmassist.server.model;

import com.fasterxml.jackson.annotation.JsonIgnore;
import com.ziroby.dmassist.gwtable.model.Entity;
import com.ziroby.dmassist.model.EnhancedEntity;
import com.ziroby.dmassist.model.EnhancedEntityList;
import lombok.Getter;
import lombok.Setter;
import org.springframework.beans.BeanUtils;

import java.util.Collection;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;


@Setter
@Getter
public class JsonEntityList {
    private final Integer initCount;
    private final int numRounds;
    private final String time;
    private Collection<JsonEntity> entities;

    public JsonEntityList(EnhancedEntityList entityList) {
        this.setEntities(entityList.getEnhancedEntities().stream()
        .map(JsonEntity::new)
                .collect(Collectors.toList()));
        initCount = entityList.getInitCount();
        numRounds = entityList.getNumRounds();
        time = entityList.formatRoundsAsTime();

        if (initCount != null) {
            this.entities.forEach(
                    entity -> {
                        if (entity.getInitRoll() == initCount) {
                            entity.setMyTurn(true);
                        }
                    }
            );
        }
    }

}
