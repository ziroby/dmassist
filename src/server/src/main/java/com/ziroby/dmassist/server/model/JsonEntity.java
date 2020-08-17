package com.ziroby.dmassist.server.model;

import com.ziroby.dmassist.gwtable.model.Entity;
import com.ziroby.dmassist.model.EnhancedEntity;
import com.ziroby.dmassist.model.EnhancedEntityList;
import lombok.*;


@Getter
@Setter
@Builder
@NoArgsConstructor
@AllArgsConstructor
public class JsonEntity {

    private String name;
    private String abbreviation;
    private String entityType;
    private Integer initRoll;
    private Integer hitpoints;
    private Integer subdual;
    private Integer roundsLeft;

    @With
    private boolean isMyTurn;

    public JsonEntity(EnhancedEntityList entityList, EnhancedEntity entity) {
        name = entity.getName();
        abbreviation = entity.getAbbreviation();
        entityType = entity.getEntityType().toString();
        initRoll = entity.getInitRoll();
        hitpoints = entity.getHitpoints();
        subdual = entity.getSubdual();
        roundsLeft = entity.getRoundsLeft();
        isMyTurn = entity.getInitRoll().equals(entityList.getInitCount());
    }
}
