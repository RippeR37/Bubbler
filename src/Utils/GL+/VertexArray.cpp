#include "VertexArray.h"
#include "../Exception.h"

#include <utility>

namespace GL {

    VertexArray::VertexArray() {
        create();
    }
    
    VertexArray::VertexArray(VertexArray&& vao) {
        create();

        std::swap(_vaoID, vao._vaoID);
    }

    VertexArray::~VertexArray() {
        destroy();
    }

    VertexArray& VertexArray::operator=(VertexArray&& vao) {
        std::swap(_vaoID, vao._vaoID);
    }

    void VertexArray::bind() {
        glBindVertexArray(_vaoID);
    }

    void VertexArray::unbind() {
        glBindVertexArray(0);
    }

    void VertexArray::drawArrays() {
        if(isDrawTargetSet && isDrawOffsetSet && isDrawCountSet)
            glDrawArrays(static_cast<GLenum>(getDrawTarget()), getDrawOffset(), getDrawCount());
        else
            throw Util::Exception::FatalError(std::string("Attempt to drawArrays() without setting target/offset/count before"));
    }

    void VertexArray::enableAttrib(GLuint index) {
        glEnableVertexAttribArray(index);
    }

    void VertexArray::disableAttrib(GLuint index) {
        glDisableVertexAttribArray(index);
    }

    void VertexArray::setAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* pointer) {
        glVertexAttribPointer(index, size, type, normalized, stride, pointer);
    }

    void VertexArray::setAttribPointers(const VertexBuffer& vertexBuffer) {
        setAttribPointers(vertexBuffer.getAttributes());
    }

    void VertexArray::setAttribPointers(const std::list<VertexAttrib>& attributes) {
        for(const VertexAttrib& attrib : attributes) {
            enableAttrib(attrib.index);
            setAttribPointer(attrib.index, attrib.size, attrib.type, attrib.normalized, attrib.stride, attrib.offset);
        }
    }

    void VertexArray::setDrawOffset(GLint offset) {
        _drawOffset = offset;
        isDrawOffsetSet = true;
    }

    void VertexArray::setDrawCount(GLsizei count) {
        _drawCount = count;
        isDrawCountSet = true;
    }

    void VertexArray::setDrawTarget(DrawTarget target) {
        _drawTarget = target;
        isDrawTargetSet = true;
    }

    GLint VertexArray::getDrawOffset() const {
        return _drawOffset;
    }

    GLsizei VertexArray::getDrawCount() const {
        return _drawCount;
    }

    VertexArray::DrawTarget VertexArray::getDrawTarget() const {
        return _drawTarget;
    }

    GLuint VertexArray::getID() const {
        return _vaoID;
    }

    void VertexArray::create() {
        glGenVertexArrays(1, &_vaoID);

        isDrawTargetSet = false;
        isDrawOffsetSet = false;
        isDrawCountSet  = false;
    }

    void VertexArray::destroy() {
        glDeleteVertexArrays(1, &_vaoID);
    }

}