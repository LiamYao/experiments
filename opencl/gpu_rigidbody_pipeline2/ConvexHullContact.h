
#ifndef _CONVEX_HULL_CONTACT_H
#define _CONVEX_HULL_CONTACT_H

#include "../broadphase_benchmark/btOpenCLArray.h"
#include "../../dynamics/basic_demo/Stubs/AdlRigidBody.h"
#include "../../dynamics/basic_demo/Stubs/ChNarrowphase.h"
#include "LinearMath/btAlignedObjectArray.h"
#include "../gpu_rigidbody_pipeline/btConvexUtility.h"
#include "../gpu_rigidbody_pipeline2/ConvexPolyhedronCL.h"
#include "../broadphase_benchmark/btOpenCLArray.h"
#include "../gpu_rigidbody_pipeline/btCollidable.h"


struct btYetAnotherAabb
{
	union
	{
		float m_min[4];
		int m_minIndices[4];
	};
	union
	{
		float m_max[4];
		//int m_signedMaxIndices[4];
		//unsigned int m_unsignedMaxIndices[4];
	};
};

struct GpuSatCollision
{
	cl_context				m_context;
	cl_device_id			m_device;
	cl_command_queue		m_queue;
	cl_kernel				m_findSeparatingAxisKernel;
	cl_kernel				m_clipHullHullKernel;
	cl_kernel				m_clipHullHullConcaveConvexKernel;
	cl_kernel				m_extractManifoldAndAddContactKernel;

	btOpenCLArray<int>		m_totalContactsOut;
	btAlignedObjectArray<Contact4>	m_hostContactOut;
	btAlignedObjectArray<int2>		m_hostPairs;

	GpuSatCollision(cl_context ctx,cl_device_id device, cl_command_queue  q );
	virtual ~GpuSatCollision();
	

	void computeConvexConvexContactsGPUSAT( const btOpenCLArray<int2>* pairs, int nPairs, 
			const btOpenCLArray<RigidBodyBase::Body>* bodyBuf, const btOpenCLArray<ChNarrowphase::ShapeData>* shapeBuf,
			btOpenCLArray<Contact4>* contactOut, int& nContacts, const ChNarrowphase::Config& cfg , 
			const btOpenCLArray<ConvexPolyhedronCL>& hostConvexData,
			const btOpenCLArray<btVector3>& vertices,
			const btOpenCLArray<btVector3>& uniqueEdges,
			const btOpenCLArray<btGpuFace>& faces,
			const btOpenCLArray<int>& indices,
			const btOpenCLArray<btCollidable>& gpuCollidables,
			const btOpenCLArray<btYetAnotherAabb>& clAabbs, 
			int numObjects,
			int maxTriConvexPairCapacity,
			btOpenCLArray<int4>& triangleConvexPairs,
			int& numTriConvexPairsOut
			);

	void computeConvexConvexContactsGPUSAT_sequential( const btOpenCLArray<int2>* pairs, int nPairs, 
			const btOpenCLArray<RigidBodyBase::Body>* bodyBuf, const btOpenCLArray<ChNarrowphase::ShapeData>* shapeBuf,
			btOpenCLArray<Contact4>* contactOut, int& nContacts, const ChNarrowphase::Config& cfg , 
			const btOpenCLArray<ConvexPolyhedronCL>& hostConvexData,
			const btOpenCLArray<btVector3>& vertices,
			const btOpenCLArray<btVector3>& uniqueEdges,
			const btOpenCLArray<btGpuFace>& faces,
			const btOpenCLArray<int>& indices,
			const btOpenCLArray<btCollidable>& gpuCollidables,
			const btOpenCLArray<btYetAnotherAabb>& clAabbs, 
			int numObjects,
			int maxTriConvexPairCapacity,
			btOpenCLArray<int4>& triangleConvexPairs,
			int& numTriConvexPairsOut
			);


		void computeConvexConvexContactsGPUSATSingle(
			int bodyIndexA, int bodyIndexB,
			int collidableIndexA, int collidableIndexB,

			const btAlignedObjectArray<RigidBodyBase::Body>* bodyBuf, 
			const btAlignedObjectArray<ChNarrowphase::ShapeData>* shapeBuf,
			btOpenCLArray<Contact4>* contactOut, 
			int& nContacts, const ChNarrowphase::Config& cfg , 
			
			const btAlignedObjectArray<ConvexPolyhedronCL>& hostConvexDataA,
			const btAlignedObjectArray<ConvexPolyhedronCL>& gpuConvexDataB,
	
			const btAlignedObjectArray<btVector3>& verticesA, 
			const btAlignedObjectArray<btVector3>& uniqueEdgesA, 
			const btAlignedObjectArray<btGpuFace>& facesA,
			const btAlignedObjectArray<int>& indicesA,
	
			const btAlignedObjectArray<btVector3>& gpuVerticesB,
			const btAlignedObjectArray<btVector3>& gpuUniqueEdgesB,
			const btAlignedObjectArray<btGpuFace>& gpuFacesB,
			const btAlignedObjectArray<int>& gpuIndicesB,

			const btAlignedObjectArray<btCollidable>& hostCollidablesA,
			const btAlignedObjectArray<btCollidable>& gpuCollidablesB);

		void clipHullHullSingle(
			int bodyIndexA, int bodyIndexB,
			int collidableIndexA, int collidableIndexB,

			const btAlignedObjectArray<RigidBodyBase::Body>* bodyBuf, 
			const btAlignedObjectArray<ChNarrowphase::ShapeData>* shapeBuf,
			btOpenCLArray<Contact4>* contactOut, 
			int& nContacts, const ChNarrowphase::Config& cfg , 
			
			const btAlignedObjectArray<ConvexPolyhedronCL>& hostConvexDataA,
			const btAlignedObjectArray<ConvexPolyhedronCL>& hostConvexDataB,
	
			const btAlignedObjectArray<btVector3>& verticesA, 
			const btAlignedObjectArray<btVector3>& uniqueEdgesA, 
			const btAlignedObjectArray<btGpuFace>& facesA,
			const btAlignedObjectArray<int>& indicesA,
	
			const btAlignedObjectArray<btVector3>& verticesB,
			const btAlignedObjectArray<btVector3>& uniqueEdgesB,
			const btAlignedObjectArray<btGpuFace>& facesB,
			const btAlignedObjectArray<int>& indicesB,

			const btAlignedObjectArray<btCollidable>& hostCollidablesA,
			const btAlignedObjectArray<btCollidable>& hostCollidablesB,
			const btVector3& sepNormalWorldSpace,int numContactsOut
			);

		void computeConcaveConvexContactsGPUSATSingle(
			int bodyIndexA, int bodyIndexB,
			int collidableIndexA, int collidableIndexB,

			const btAlignedObjectArray<RigidBodyBase::Body>* bodyBuf, 
			const btAlignedObjectArray<ChNarrowphase::ShapeData>* shapeBuf,
			btOpenCLArray<Contact4>* contactOut, 
			int& nContacts, const ChNarrowphase::Config& cfg , 
			const btAlignedObjectArray<ConvexPolyhedronCL>& hostConvexDataB,
			const btAlignedObjectArray<btVector3>& verticesB,
			const btAlignedObjectArray<btVector3>& uniqueEdgesB,
			const btAlignedObjectArray<btGpuFace>& facesB,
			const btAlignedObjectArray<int>& indicesB,
			const btAlignedObjectArray<btCollidable>& hostCollidablesB,
			btAlignedObjectArray<btYetAnotherAabb>& clAabbs, 
			int numObjects,
			int maxTriConvexPairCapacity,
			btAlignedObjectArray<int4>& triangleConvexPairs,
			int& numTriConvexPairsOut);

};

#endif //_CONVEX_HULL_CONTACT_H