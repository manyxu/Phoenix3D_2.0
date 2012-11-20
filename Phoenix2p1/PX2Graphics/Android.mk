LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := PX2Graphics

LOCAL_SRC_FILES := \
Renderers/OpenGLES2Renderer/PX2OpenGLES2IndexBuffer.cpp \
Renderers/OpenGLES2Renderer/PX2OpenGLES2Mapping.cpp \
Renderers/OpenGLES2Renderer/PX2OpenGLES2MaterialPass.cpp \
Renderers/OpenGLES2Renderer/PX2OpenGLES2PixelShader.cpp \
Renderers/OpenGLES2Renderer/PX2OpenGLES2Renderer.cpp \
Renderers/OpenGLES2Renderer/PX2OpenGLES2RendererData.cpp \
Renderers/OpenGLES2Renderer/PX2OpenGLES2RenderTarget.cpp \
Renderers/OpenGLES2Renderer/PX2OpenGLES2Shader.cpp \
Renderers/OpenGLES2Renderer/PX2OpenGLES2Texture1D.cpp \
Renderers/OpenGLES2Renderer/PX2OpenGLES2Texture2D.cpp \
Renderers/OpenGLES2Renderer/PX2OpenGLES2Texture3D.cpp \
Renderers/OpenGLES2Renderer/PX2OpenGLES2TextureCube.cpp \
Renderers/OpenGLES2Renderer/PX2OpenGLES2VertexBuffer.cpp \
Renderers/OpenGLES2Renderer/PX2OpenGLES2VertexFormat.cpp \
Renderers/OpenGLES2Renderer/PX2OpenGLES2VertexShader.cpp \
PX2Renderer.cpp \
PX2AlphaProperty.cpp \
PX2Bound.cpp \
PX2BoxSurface.cpp \
PX2Buffer.cpp \
PX2Camera.cpp \
PX2CameraModelDVectorConstant.cpp \
PX2CameraModelPositionConstant.cpp \
PX2CameraNode.cpp \
PX2CameraWorldDVectorConstant.cpp \
PX2CameraWorldPositionConstant.cpp \
PX2ClodMesh.cpp \
PX2CollapseRecord.cpp \
PX2CollapseRecordArray.cpp \
PX2Color.cpp \
PX2Controlledable.cpp \
PX2Controller.cpp \
PX2CreateClodMesh.cpp \
PX2Culler.cpp \
PX2CullProperty.cpp \
PX2CurveMesh.cpp \
PX2CurveSegment.cpp \
PX2DepthProperty.cpp \
PX2DlodNode.cpp \
PX2Float2Array.cpp \
PX2FloatArray.cpp \
PX2GlobalMaterial.cpp \
PX2GraphicsRoot.cpp \
PX2HalfFloat.cpp \
PX2ImageProcessing.cpp \
PX2ImageProcessing2.cpp \
PX2IndexBuffer.cpp \
PX2KeyframeController.cpp \
PX2Light.cpp \
PX2LightAmbientConstant.cpp \
PX2LightAttenuationConstant.cpp \
PX2LightDiffuseConstant.cpp \
PX2LightModelDVectorConstant.cpp \
PX2LightModelPositionConstant.cpp \
PX2LightNode.cpp \
PX2LightSpecularConstant.cpp \
PX2LightSpotConstant.cpp \
PX2LightWorldDVectorConstant.cpp \
PX2LightWorldPositionConstant.cpp \
PX2Material.cpp \
PX2MaterialInstance.cpp \
PX2MaterialPass.cpp \
PX2MaterialTechnique.cpp \
PX2Movable.cpp \
PX2Node.cpp \
PX2OffsetProperty.cpp \
PX2Picker.cpp \
PX2PickRecord.cpp \
PX2PixelShader.cpp \
PX2PMatrixConstant.cpp \
PX2Polypoint.cpp \
PX2Polysegment.cpp \
PX2Projector.cpp \
PX2ProjectorMatrixConstant.cpp \
PX2ProjectorWorldPositionConstant.cpp \
PX2PVMatrixConstant.cpp \
PX2PVWMatrixConstant.cpp \
PX2Renderable.cpp \
PX2RenderTarget.cpp \
PX2ScreenTarget.cpp \
PX2Shader.cpp \
PX2ShaderFloat.cpp \
PX2ShaderParameters.cpp \
PX2Shine.cpp \
PX2ShineAmbientConstant.cpp \
PX2ShineDiffuseConstant.cpp \
PX2ShineEmissiveConstant.cpp \
PX2ShineSpecularConstant.cpp \
PX2SkinController.cpp \
PX2SpecializedIO.cpp \
PX2StandardMaterial.cpp \
PX2StandardMesh.cpp \
PX2StencilProperty.cpp \
PX2SwitchNode.cpp \
PX2Texture.cpp \
PX2Texture1D.cpp \
PX2Texture2D.cpp \
PX2Texture2DMaterial.cpp \
PX2Texture3D.cpp \
PX2TextureCube.cpp \
PX2Transform.cpp \
PX2TransformController.cpp \
PX2Triangles.cpp \
PX2TriFan.cpp \
PX2TriMesh.cpp \
PX2TriStrip.cpp \
PX2VertexBuffer.cpp \
PX2VertexBufferAccessor.cpp \
PX2VertexColor4Material.cpp \
PX2VertexFormat.cpp \
PX2VertexShader.cpp \
PX2VisibleSet.cpp \
PX2VMatrixConstant.cpp \
PX2VWMatrixConstant.cpp \
PX2WireProperty.cpp \
PX2WMatrixConstant.cpp

LOCAL_EXPORT_LDLIBS := -lGLESv2

LOCAL_LDLIBS := -lGLESv1_CM -ldl -llog -lGLESv2

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/..

LOCAL_C_INCLUDES := $(LOCAL_PATH)/.. \
$(LOCAL_PATH)/Renderers/OpenGLES2Renderer/ \
$(PX2_ROOT)/PX2SDK/Include/ \
$(PX2_ROOT)/ThirdPartiesLibs/OGLES/

include $(BUILD_STATIC_LIBRARY)
