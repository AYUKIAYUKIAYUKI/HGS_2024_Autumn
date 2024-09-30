#pragma once

#pragma push_macro("new")
#undef new

#ifndef _MBCS
#error "Multi-byte character set is not enabled."
#endif // !_MBCS

#ifndef NOMINMAX 
#error "Please define NOMINMAX macro before including windows.h."
#endif // !NOMINMAX

// Includes
#include "d3dx9.h"
#include <string>

namespace HGSAutumn240930
{
	// NOTHING
}

namespace HGSAutumn240930::Collision
{
	using Point2D = D3DXVECTOR2;

	struct Circle
	{
		D3DXVECTOR2 c;
		float r;

		Circle(
			D3DXVECTOR2 _c = D3DXVECTOR2(0.0f, 0.0f),
			float _r = 0.0f)
			: c(_c)
			, r(_r)
		{ /* do nothing */ }
	};

	struct Ellipse
	{
		D3DXVECTOR2 c;
		D3DXVECTOR2 r;
		float radian;

		Ellipse(
			D3DXVECTOR2 _c = D3DXVECTOR2(0.0f, 0.0f),
			D3DXVECTOR2 _r = D3DXVECTOR2(0.0f, 0.0f),
			float _radian = 0.0f)
			: c(_c)
			, r(_r)
			, radian(_radian)
		{ /* do nothing */ }
	};

	struct Sphere
	{
		D3DXVECTOR3 c;
		float r;

		Sphere(
			D3DXVECTOR3 _c = D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			float _r = 0.0f)
			: c(_c)
			, r(_r)
		{ /* do nothing */ }
	};

	struct Rectangle
	{
		D3DXVECTOR2 c;
		D3DXVECTOR2 e;
		float radian;

		Rectangle(
			D3DXVECTOR3 _c = D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXVECTOR3 _e = D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			float _radian = 0.0f)
			: c(_c)
			, e(_e)
			, radian(_radian)
		{ /* do nothing */ }
	};

	struct LineSegment2D
	{
		D3DXVECTOR2 p1;
		D3DXVECTOR2 p2;

		LineSegment2D(
			D3DXVECTOR2 _p1 = D3DXVECTOR2(0.0f, 0.0f),
			D3DXVECTOR2 _p2 = D3DXVECTOR2(0.0f, 0.0f))
			: p1(_p1)
			, p2(_p2)
		{ /* do nothing */ }
	};

	struct LineSegment3D
	{
		D3DXVECTOR3 p1;
		D3DXVECTOR3 p2;

		LineSegment3D(
			D3DXVECTOR3 _p1 = D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXVECTOR3 _p2 = D3DXVECTOR3(0.0f, 0.0f, 0.0f))
			: p1(_p1)
			, p2(_p2)
		{ /* do nothing */ }
	};

	struct Line
	{
		D3DXVECTOR2 base;
		D3DXVECTOR2 dir;

		Line(
			D3DXVECTOR2 _base = D3DXVECTOR2(0.0f, 0.0f),
			D3DXVECTOR2 _dir = D3DXVECTOR2(0.0f, 0.0f))
			: base(_base)
			, dir(_dir)
		{ /* do nothing */ }
	};

	struct Range
	{
		float min;
		float max;

		Range(
			float _min = 0.0f,
			float _max = 0.0f)
			: min(_min)
			, max(_max)
		{ /* do nothing */ }
	};

	bool IsCollisionCircleVsCircle(const Circle& inCircle1, const Circle& inCircle2);
	bool IsCollisionSphereVsSphere(const Sphere& inSphere1, const Sphere& inSphere2);
	bool IsCollisionRectVsRect(const Rectangle& inRect1, const Rectangle& inRect2);
	bool IsCollisionRectVsRect2D(const D3DXVECTOR2& inPos1, const D3DXVECTOR2& inSize1, const D3DXVECTOR2& inPos2, const D3DXVECTOR2& inSize2);
	bool IsCollisionCircleVsPoint(const Circle& inCircle, const D3DXVECTOR2& inPos);
	bool IsCollisionEllipseVsPoint(const Ellipse& inEllipse, const D3DXVECTOR2& inPos);
	LineSegment2D GetRectEdge(const Rectangle& inRect, const int& inPoint);
	bool IsSeparatingAxisForRect(const LineSegment2D& inAxis, const Rectangle& inRect);
	D3DXVECTOR2 RotVec90(const D3DXVECTOR2& inVec);
	float GetDegreeToRadian(const float& inDegree);
	float GetRadianToDegree(const float& inRadian);
	D3DXVECTOR2 GetRotateVec(const D3DXVECTOR2& inVec, const float& inRadian);
	bool IsEqualVectors(const D3DXVECTOR2& inVec1, const D3DXVECTOR2& inVec2);
	D3DXVECTOR2 GetUnitVec(D3DXVECTOR2 inVec);
	float GetVecLength2D(const D3DXVECTOR2& inVec);
	D3DXVECTOR2 GetDivideVec(D3DXVECTOR2 inVec, const float& inLength);
	bool EqualFloats(const float& a, const float& b);
	bool IsParallelVec(const D3DXVECTOR2& inVec1, const D3DXVECTOR2& inVec2);
	bool IsVerticalVec(const D3DXVECTOR2& inVec1, const D3DXVECTOR2& inVec2);
	float DotProduct2D(const D3DXVECTOR2& inVec1, const D3DXVECTOR2& inVec2);
	float GetCross(const D3DXVECTOR2& inVec1, const D3DXVECTOR2& inVec2);
	bool OnOneSide(const Line& inAxis, const LineSegment2D& inSegment);
	bool OverLapping(const float& inMin1, const float& inMax1, const float& inMin2, const float& inMax2);
	bool IsSegmentsCollide(const LineSegment2D& inSegment1, const LineSegment2D& inSegment2);
	Range GetMaxMinRange(const Range& inRange1, const Range& inRange2);
	Range GetSortRange(const Range& inRange);
	D3DXVECTOR2 GetNegateVec(D3DXVECTOR2 inVec);
	Range GetProjectSegment(const LineSegment2D& inSegment, const D3DXVECTOR2& inOnto);
	bool IsoverLappingRanges(const Range& inRange1, const Range& inRange2);
	D3DXVECTOR2 ProjectVec(const D3DXVECTOR2& inProject, const D3DXVECTOR2& inOnto);
	float GetNorm(D3DXVECTOR2 inVec);
	float GetVec2DLength(D3DXVECTOR2 inVec);
	Point2D GetProjectPoint(const LineSegment2D& inSegment, const Point2D& inPoint);
	D3DXVECTOR2 GetReflectionPoint(const LineSegment2D& inSegment, const Point2D& inPoint);
	Point2D GetCrossPoint(const LineSegment2D& inSegment1, const LineSegment2D& inSegment2);
	float ClampOnRange(const float& inX, const float& inMin, const float& inMax);
	float GetDistanceLinePoint(const LineSegment2D& inLine, const Point2D& inPoint);
	float GetDistanceSegmentPoint(const LineSegment2D& inSegment, const Point2D& inPoint);
	float GetSegmentDistance(const LineSegment2D& inSegment1, const LineSegment2D& inSegment2);
	bool IsPointInsideRectangle(const D3DXVECTOR3& point, const Rectangle& rect);
}

namespace HGSAutumn240930::String
{
#pragma region Print
	inline std::string Print()
	{
		return "";
	}

	template<typename T, typename... Args>
	inline std::string Print(const T& head, const Args&... args)
	{
		std::ostringstream oss;
		oss << head;
		return oss.str() + Print(args...);
	}
#pragma endregion
}

// Add to source as needed.
#if 0
using namespace HGSAutumn240930;
using namespace HGSAutumn240930::Collision;
using namespace HGSAutumn240930::String;
#endif

#pragma pop_macro("new")
