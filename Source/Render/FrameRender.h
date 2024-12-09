#pragma once
#include <memory>
#include "MultiAttributedText.h"
#include "IRenderObject.h"

class FrameRender
{
private:
    using SharedRenderObject = std::shared_ptr<const IRenderObject>;
    std::vector<SharedRenderObject> _renderObjects;
    MultiAttributedText _text;
    
public:
    FrameRender() = default;

    template <typename RenderObjectImpl, typename... ConstructorArguments>
    std::enable_if_t<std::is_base_of_v<IRenderObject, RenderObjectImpl>>
    AddRenderObject(ConstructorArguments... arguments);
    void Render();
    void Display() const;

private:
    void ReserveMemory();
    int EvaluateImageLength();
};

template <typename RenderObjectImpl, typename... ConstructorArguments>
std::enable_if_t<std::is_base_of_v<IRenderObject, RenderObjectImpl>>
FrameRender::AddRenderObject(ConstructorArguments... arguments)
{
    IRenderObject* rawPointer = (IRenderObject*)new RenderObjectImpl(arguments...);
    std::shared_ptr<IRenderObject> sharedPointer = std::shared_ptr<IRenderObject>(rawPointer);
    _renderObjects.push_back(sharedPointer);
}