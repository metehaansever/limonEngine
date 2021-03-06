//
// Created by engin on 12.12.2018.
//

#ifndef LIMONENGINE_COMBININGOBJECT_H
#define LIMONENGINE_COMBININGOBJECT_H

#include <cstdint>
#include <vector>
#include <map>
#include <string>
class GLHelper;
class GLSLProgram;

class QuadRenderBase {
    uint_fast32_t vao, ebo;
    std::vector<uint32_t> bufferObjects;
    std::map<std::string, int32_t> textureAttachments;

    virtual void initializeProgram() = 0;
protected:
    GLSLProgram* program = nullptr;
    GLHelper* glHelper = nullptr;
public:
    QuadRenderBase(GLHelper* glHelper);

    void setSourceTexture(std::string samplerName, int32_t textureID) {
        textureAttachments[samplerName] = textureID;
    }
    bool removeSourceTexture(std::string samplerName) {
        auto mapElement = textureAttachments.find(samplerName);
        if(mapElement != textureAttachments.end()) {
            textureAttachments.erase(mapElement);
            return true;
        }
        return false;
    }
    virtual void render();

    virtual ~QuadRenderBase() {}
};


#endif //LIMONENGINE_COMBININGOBJECT_H
