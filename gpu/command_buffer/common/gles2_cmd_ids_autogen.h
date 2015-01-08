// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// This file is auto-generated from
// gpu/command_buffer/build_gles2_cmd_buffer.py
// It's formatted by clang-format using chromium coding style:
//    clang-format -i -style=chromium filename
// DO NOT EDIT!

#ifndef GPU_COMMAND_BUFFER_COMMON_GLES2_CMD_IDS_AUTOGEN_H_
#define GPU_COMMAND_BUFFER_COMMON_GLES2_CMD_IDS_AUTOGEN_H_

#define GLES2_COMMAND_LIST(OP)                           \
  OP(ActiveTexture)                            /* 256 */ \
  OP(AttachShader)                             /* 257 */ \
  OP(BindAttribLocationBucket)                 /* 258 */ \
  OP(BindBuffer)                               /* 259 */ \
  OP(BindFramebuffer)                          /* 260 */ \
  OP(BindRenderbuffer)                         /* 261 */ \
  OP(BindSampler)                              /* 262 */ \
  OP(BindTexture)                              /* 263 */ \
  OP(BindTransformFeedback)                    /* 264 */ \
  OP(BlendColor)                               /* 265 */ \
  OP(BlendEquation)                            /* 266 */ \
  OP(BlendEquationSeparate)                    /* 267 */ \
  OP(BlendFunc)                                /* 268 */ \
  OP(BlendFuncSeparate)                        /* 269 */ \
  OP(BufferData)                               /* 270 */ \
  OP(BufferSubData)                            /* 271 */ \
  OP(CheckFramebufferStatus)                   /* 272 */ \
  OP(Clear)                                    /* 273 */ \
  OP(ClearColor)                               /* 274 */ \
  OP(ClearDepthf)                              /* 275 */ \
  OP(ClearStencil)                             /* 276 */ \
  OP(ColorMask)                                /* 277 */ \
  OP(CompileShader)                            /* 278 */ \
  OP(CompressedTexImage2DBucket)               /* 279 */ \
  OP(CompressedTexImage2D)                     /* 280 */ \
  OP(CompressedTexSubImage2DBucket)            /* 281 */ \
  OP(CompressedTexSubImage2D)                  /* 282 */ \
  OP(CopyBufferSubData)                        /* 283 */ \
  OP(CopyTexImage2D)                           /* 284 */ \
  OP(CopyTexSubImage2D)                        /* 285 */ \
  OP(CreateProgram)                            /* 286 */ \
  OP(CreateShader)                             /* 287 */ \
  OP(CullFace)                                 /* 288 */ \
  OP(DeleteBuffersImmediate)                   /* 289 */ \
  OP(DeleteFramebuffersImmediate)              /* 290 */ \
  OP(DeleteProgram)                            /* 291 */ \
  OP(DeleteRenderbuffersImmediate)             /* 292 */ \
  OP(DeleteSamplersImmediate)                  /* 293 */ \
  OP(DeleteShader)                             /* 294 */ \
  OP(DeleteTexturesImmediate)                  /* 295 */ \
  OP(DeleteTransformFeedbacksImmediate)        /* 296 */ \
  OP(DepthFunc)                                /* 297 */ \
  OP(DepthMask)                                /* 298 */ \
  OP(DepthRangef)                              /* 299 */ \
  OP(DetachShader)                             /* 300 */ \
  OP(Disable)                                  /* 301 */ \
  OP(DisableVertexAttribArray)                 /* 302 */ \
  OP(DrawArrays)                               /* 303 */ \
  OP(DrawElements)                             /* 304 */ \
  OP(Enable)                                   /* 305 */ \
  OP(EnableVertexAttribArray)                  /* 306 */ \
  OP(Finish)                                   /* 307 */ \
  OP(Flush)                                    /* 308 */ \
  OP(FramebufferRenderbuffer)                  /* 309 */ \
  OP(FramebufferTexture2D)                     /* 310 */ \
  OP(FramebufferTextureLayer)                  /* 311 */ \
  OP(FrontFace)                                /* 312 */ \
  OP(GenBuffersImmediate)                      /* 313 */ \
  OP(GenerateMipmap)                           /* 314 */ \
  OP(GenFramebuffersImmediate)                 /* 315 */ \
  OP(GenRenderbuffersImmediate)                /* 316 */ \
  OP(GenSamplersImmediate)                     /* 317 */ \
  OP(GenTexturesImmediate)                     /* 318 */ \
  OP(GenTransformFeedbacksImmediate)           /* 319 */ \
  OP(GetActiveAttrib)                          /* 320 */ \
  OP(GetActiveUniform)                         /* 321 */ \
  OP(GetAttachedShaders)                       /* 322 */ \
  OP(GetAttribLocation)                        /* 323 */ \
  OP(GetBooleanv)                              /* 324 */ \
  OP(GetBufferParameteriv)                     /* 325 */ \
  OP(GetError)                                 /* 326 */ \
  OP(GetFloatv)                                /* 327 */ \
  OP(GetFramebufferAttachmentParameteriv)      /* 328 */ \
  OP(GetIntegerv)                              /* 329 */ \
  OP(GetInternalformativ)                      /* 330 */ \
  OP(GetProgramiv)                             /* 331 */ \
  OP(GetProgramInfoLog)                        /* 332 */ \
  OP(GetRenderbufferParameteriv)               /* 333 */ \
  OP(GetSamplerParameterfv)                    /* 334 */ \
  OP(GetSamplerParameteriv)                    /* 335 */ \
  OP(GetShaderiv)                              /* 336 */ \
  OP(GetShaderInfoLog)                         /* 337 */ \
  OP(GetShaderPrecisionFormat)                 /* 338 */ \
  OP(GetShaderSource)                          /* 339 */ \
  OP(GetString)                                /* 340 */ \
  OP(GetTexParameterfv)                        /* 341 */ \
  OP(GetTexParameteriv)                        /* 342 */ \
  OP(GetUniformfv)                             /* 343 */ \
  OP(GetUniformiv)                             /* 344 */ \
  OP(GetUniformLocation)                       /* 345 */ \
  OP(GetVertexAttribfv)                        /* 346 */ \
  OP(GetVertexAttribiv)                        /* 347 */ \
  OP(GetVertexAttribPointerv)                  /* 348 */ \
  OP(Hint)                                     /* 349 */ \
  OP(InvalidateFramebufferImmediate)           /* 350 */ \
  OP(InvalidateSubFramebufferImmediate)        /* 351 */ \
  OP(IsBuffer)                                 /* 352 */ \
  OP(IsEnabled)                                /* 353 */ \
  OP(IsFramebuffer)                            /* 354 */ \
  OP(IsProgram)                                /* 355 */ \
  OP(IsRenderbuffer)                           /* 356 */ \
  OP(IsSampler)                                /* 357 */ \
  OP(IsShader)                                 /* 358 */ \
  OP(IsTexture)                                /* 359 */ \
  OP(IsTransformFeedback)                      /* 360 */ \
  OP(LineWidth)                                /* 361 */ \
  OP(LinkProgram)                              /* 362 */ \
  OP(PauseTransformFeedback)                   /* 363 */ \
  OP(PixelStorei)                              /* 364 */ \
  OP(PolygonOffset)                            /* 365 */ \
  OP(ReadBuffer)                               /* 366 */ \
  OP(ReadPixels)                               /* 367 */ \
  OP(ReleaseShaderCompiler)                    /* 368 */ \
  OP(RenderbufferStorage)                      /* 369 */ \
  OP(ResumeTransformFeedback)                  /* 370 */ \
  OP(SampleCoverage)                           /* 371 */ \
  OP(SamplerParameterf)                        /* 372 */ \
  OP(SamplerParameterfvImmediate)              /* 373 */ \
  OP(SamplerParameteri)                        /* 374 */ \
  OP(SamplerParameterivImmediate)              /* 375 */ \
  OP(Scissor)                                  /* 376 */ \
  OP(ShaderBinary)                             /* 377 */ \
  OP(ShaderSourceBucket)                       /* 378 */ \
  OP(StencilFunc)                              /* 379 */ \
  OP(StencilFuncSeparate)                      /* 380 */ \
  OP(StencilMask)                              /* 381 */ \
  OP(StencilMaskSeparate)                      /* 382 */ \
  OP(StencilOp)                                /* 383 */ \
  OP(StencilOpSeparate)                        /* 384 */ \
  OP(TexImage2D)                               /* 385 */ \
  OP(TexImage3D)                               /* 386 */ \
  OP(TexParameterf)                            /* 387 */ \
  OP(TexParameterfvImmediate)                  /* 388 */ \
  OP(TexParameteri)                            /* 389 */ \
  OP(TexParameterivImmediate)                  /* 390 */ \
  OP(TexStorage3D)                             /* 391 */ \
  OP(TexSubImage2D)                            /* 392 */ \
  OP(TexSubImage3D)                            /* 393 */ \
  OP(Uniform1f)                                /* 394 */ \
  OP(Uniform1fvImmediate)                      /* 395 */ \
  OP(Uniform1i)                                /* 396 */ \
  OP(Uniform1ivImmediate)                      /* 397 */ \
  OP(Uniform1ui)                               /* 398 */ \
  OP(Uniform1uivImmediate)                     /* 399 */ \
  OP(Uniform2f)                                /* 400 */ \
  OP(Uniform2fvImmediate)                      /* 401 */ \
  OP(Uniform2i)                                /* 402 */ \
  OP(Uniform2ivImmediate)                      /* 403 */ \
  OP(Uniform2ui)                               /* 404 */ \
  OP(Uniform2uivImmediate)                     /* 405 */ \
  OP(Uniform3f)                                /* 406 */ \
  OP(Uniform3fvImmediate)                      /* 407 */ \
  OP(Uniform3i)                                /* 408 */ \
  OP(Uniform3ivImmediate)                      /* 409 */ \
  OP(Uniform3ui)                               /* 410 */ \
  OP(Uniform3uivImmediate)                     /* 411 */ \
  OP(Uniform4f)                                /* 412 */ \
  OP(Uniform4fvImmediate)                      /* 413 */ \
  OP(Uniform4i)                                /* 414 */ \
  OP(Uniform4ivImmediate)                      /* 415 */ \
  OP(Uniform4ui)                               /* 416 */ \
  OP(Uniform4uivImmediate)                     /* 417 */ \
  OP(UniformMatrix2fvImmediate)                /* 418 */ \
  OP(UniformMatrix2x3fvImmediate)              /* 419 */ \
  OP(UniformMatrix2x4fvImmediate)              /* 420 */ \
  OP(UniformMatrix3fvImmediate)                /* 421 */ \
  OP(UniformMatrix3x2fvImmediate)              /* 422 */ \
  OP(UniformMatrix3x4fvImmediate)              /* 423 */ \
  OP(UniformMatrix4fvImmediate)                /* 424 */ \
  OP(UniformMatrix4x2fvImmediate)              /* 425 */ \
  OP(UniformMatrix4x3fvImmediate)              /* 426 */ \
  OP(UseProgram)                               /* 427 */ \
  OP(ValidateProgram)                          /* 428 */ \
  OP(VertexAttrib1f)                           /* 429 */ \
  OP(VertexAttrib1fvImmediate)                 /* 430 */ \
  OP(VertexAttrib2f)                           /* 431 */ \
  OP(VertexAttrib2fvImmediate)                 /* 432 */ \
  OP(VertexAttrib3f)                           /* 433 */ \
  OP(VertexAttrib3fvImmediate)                 /* 434 */ \
  OP(VertexAttrib4f)                           /* 435 */ \
  OP(VertexAttrib4fvImmediate)                 /* 436 */ \
  OP(VertexAttribI4i)                          /* 437 */ \
  OP(VertexAttribI4ivImmediate)                /* 438 */ \
  OP(VertexAttribI4ui)                         /* 439 */ \
  OP(VertexAttribI4uivImmediate)               /* 440 */ \
  OP(VertexAttribIPointer)                     /* 441 */ \
  OP(VertexAttribPointer)                      /* 442 */ \
  OP(Viewport)                                 /* 443 */ \
  OP(BlitFramebufferCHROMIUM)                  /* 444 */ \
  OP(RenderbufferStorageMultisampleCHROMIUM)   /* 445 */ \
  OP(RenderbufferStorageMultisampleEXT)        /* 446 */ \
  OP(FramebufferTexture2DMultisampleEXT)       /* 447 */ \
  OP(TexStorage2DEXT)                          /* 448 */ \
  OP(GenQueriesEXTImmediate)                   /* 449 */ \
  OP(DeleteQueriesEXTImmediate)                /* 450 */ \
  OP(BeginQueryEXT)                            /* 451 */ \
  OP(BeginTransformFeedback)                   /* 452 */ \
  OP(EndQueryEXT)                              /* 453 */ \
  OP(EndTransformFeedback)                     /* 454 */ \
  OP(InsertEventMarkerEXT)                     /* 455 */ \
  OP(PushGroupMarkerEXT)                       /* 456 */ \
  OP(PopGroupMarkerEXT)                        /* 457 */ \
  OP(GenVertexArraysOESImmediate)              /* 458 */ \
  OP(DeleteVertexArraysOESImmediate)           /* 459 */ \
  OP(IsVertexArrayOES)                         /* 460 */ \
  OP(BindVertexArrayOES)                       /* 461 */ \
  OP(SwapBuffers)                              /* 462 */ \
  OP(GetMaxValueInBufferCHROMIUM)              /* 463 */ \
  OP(EnableFeatureCHROMIUM)                    /* 464 */ \
  OP(ResizeCHROMIUM)                           /* 465 */ \
  OP(GetRequestableExtensionsCHROMIUM)         /* 466 */ \
  OP(RequestExtensionCHROMIUM)                 /* 467 */ \
  OP(GetProgramInfoCHROMIUM)                   /* 468 */ \
  OP(GetTranslatedShaderSourceANGLE)           /* 469 */ \
  OP(PostSubBufferCHROMIUM)                    /* 470 */ \
  OP(TexImageIOSurface2DCHROMIUM)              /* 471 */ \
  OP(CopyTextureCHROMIUM)                      /* 472 */ \
  OP(DrawArraysInstancedANGLE)                 /* 473 */ \
  OP(DrawElementsInstancedANGLE)               /* 474 */ \
  OP(VertexAttribDivisorANGLE)                 /* 475 */ \
  OP(GenMailboxCHROMIUM)                       /* 476 */ \
  OP(ProduceTextureCHROMIUMImmediate)          /* 477 */ \
  OP(ProduceTextureDirectCHROMIUMImmediate)    /* 478 */ \
  OP(ConsumeTextureCHROMIUMImmediate)          /* 479 */ \
  OP(CreateAndConsumeTextureCHROMIUMImmediate) /* 480 */ \
  OP(BindUniformLocationCHROMIUMBucket)        /* 481 */ \
  OP(GenValuebuffersCHROMIUMImmediate)         /* 482 */ \
  OP(DeleteValuebuffersCHROMIUMImmediate)      /* 483 */ \
  OP(IsValuebufferCHROMIUM)                    /* 484 */ \
  OP(BindValuebufferCHROMIUM)                  /* 485 */ \
  OP(SubscribeValueCHROMIUM)                   /* 486 */ \
  OP(PopulateSubscribedValuesCHROMIUM)         /* 487 */ \
  OP(UniformValuebufferCHROMIUM)               /* 488 */ \
  OP(BindTexImage2DCHROMIUM)                   /* 489 */ \
  OP(ReleaseTexImage2DCHROMIUM)                /* 490 */ \
  OP(TraceBeginCHROMIUM)                       /* 491 */ \
  OP(TraceEndCHROMIUM)                         /* 492 */ \
  OP(AsyncTexSubImage2DCHROMIUM)               /* 493 */ \
  OP(AsyncTexImage2DCHROMIUM)                  /* 494 */ \
  OP(WaitAsyncTexImage2DCHROMIUM)              /* 495 */ \
  OP(WaitAllAsyncTexImage2DCHROMIUM)           /* 496 */ \
  OP(DiscardFramebufferEXTImmediate)           /* 497 */ \
  OP(LoseContextCHROMIUM)                      /* 498 */ \
  OP(InsertSyncPointCHROMIUM)                  /* 499 */ \
  OP(WaitSyncPointCHROMIUM)                    /* 500 */ \
  OP(DrawBuffersEXTImmediate)                  /* 501 */ \
  OP(DiscardBackbufferCHROMIUM)                /* 502 */ \
  OP(ScheduleOverlayPlaneCHROMIUM)             /* 503 */ \
  OP(SwapInterval)                             /* 504 */ \
  OP(MatrixLoadfCHROMIUMImmediate)             /* 505 */ \
  OP(MatrixLoadIdentityCHROMIUM)               /* 506 */ \
  OP(BlendBarrierKHR)                          /* 507 */

enum CommandId {
  kStartPoint = cmd::kLastCommonId,  // All GLES2 commands start after this.
#define GLES2_CMD_OP(name) k##name,
  GLES2_COMMAND_LIST(GLES2_CMD_OP)
#undef GLES2_CMD_OP
      kNumCommands
};

#endif  // GPU_COMMAND_BUFFER_COMMON_GLES2_CMD_IDS_AUTOGEN_H_
