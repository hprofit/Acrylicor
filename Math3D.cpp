#include "Math3D.h"
#include <math.h>
#include "AcrylicorTypedefs.h"

bool StaticPointToStaticCircle(const Vector3D & pos, const Vector3D & center, float radius)
{
	return Vector3D::SquareDistance(pos, center) <= (radius * radius);
}

bool StaticPointToStaticRect(const Vector3D & pos, const Vector3D & rect, const float halfWidth, const float halfHeight)
{
	float left = rect.getX() - halfWidth,
		right = rect.getX() + halfWidth,
		top = rect.getY() + halfHeight,
		bottom = rect.getY() - halfHeight;
	return (pos.getX() >= left && pos.getX() <= right && pos.getY() <= top && pos.getY() >= bottom);
}

bool StaticCircleToStaticCircle(const Vector3D & center0, const float radius0, const Vector3D & center1, const float radius1)
{
	float radiusSum = radius0 + radius1;
	return Vector3D::SquareDistance(center0, center1) <= (radiusSum * radiusSum);
}

bool StaticRectToStaticRect(const Vector3D & rect0, const float halfWidth0, const float halfHeight0, const Vector3D & rect1, const float halfWidth1, const float halfHeight1)
{
	float left0 = rect0.getX() - halfWidth0,
		right0 = rect0.getX() + halfWidth0,
		top0 = rect0.getY() + halfHeight0,
		bottom0 = rect0.getY() - halfHeight0,
		left1 = rect1.getX() - halfWidth1,
		right1 = rect1.getX() + halfWidth1,
		top1 = rect1.getY() + halfHeight1,
		bottom1 = rect1.getY() - halfHeight1;

	return !(top1 < bottom0 || left1 > right0 || right1 < left0 || bottom1 > top0);
}

bool StaticRectToStaticCircle(const Vector3D & rect, const float halfWidth, const float halfHeight, const Vector3D center, const float radius)
{
	Vector3D snappedPoint = center;
	float left = rect.getX() - halfWidth;
	float right = rect.getX() + halfWidth;
	float top = rect.getY() + halfHeight;
	float bottom = rect.getY() - halfHeight;


	if (snappedPoint.getX() > right)	snappedPoint.setX(right);
	else if (snappedPoint.getX() < left)	snappedPoint.setX(left);

	if (snappedPoint.getY() > top)	snappedPoint.setY(top);
	else if (snappedPoint.getY() < bottom)	snappedPoint.setY(bottom);

	return Vector3D::SquareDistance(snappedPoint, center) < (radius * radius);
}

float StaticPointToStaticLineSegment(const Vector3D & P, const LineSegment3D & LS)
{
	return Vector3D::Dot(P, LS.getNorm()) - LS.getNDotP0();
}

float AnimatedPointToStaticLineSegment(const Vector3D & Ps, const Vector3D & Pe, const LineSegment3D & LS, Vector3D & Pi)
{
	Vector3D PsPe = Pe - Ps;
	float	nDotP0 = LS.getNDotP0(),
		nDotPs = Vector3D::Dot(LS.getNorm(), Ps),
		nDotPe = Vector3D::Dot(LS.getNorm(), Pe),
		nDotPsPe = Vector3D::Dot(LS.getNorm(), PsPe);

	// Point will not collide in this iteration
	if ((nDotPs < nDotP0 && nDotPe < nDotP0) || (nDotPs > nDotP0 && nDotPe > nDotP0) || nDotPsPe == 0.0f)
		return -1.0f;

	float t = (nDotP0 - Vector3D::Dot(LS.getNorm(), Ps)) / (nDotPsPe);
	Vector3D	collisionPoint = (PsPe * t) - Ps,
		LSPeSubLSPs = LS.getP1() - LS.getP0();

	// Point of intersection with the infinite line but not finite line
	if (Vector3D::Dot(collisionPoint - LS.getP0(), LSPeSubLSPs) < 0 ||
		Vector3D::Dot(collisionPoint - LS.getP1(), LSPeSubLSPs) < 0)
		return -1.0f;

	Pi = collisionPoint;
	return t;
}

float AnimatedCircleToStaticLineSegment(const Vector3D & Ps, const Vector3D & Pe, const float Radius, const LineSegment3D & LS, Vector3D & Pi)
{
	Vector3D v = Pe - Ps, LSNorm = LS.getNorm(),
		collisionPoint, cPsubLSPs, cPsubLSPe, lineP1, lineP0;

	float	nDotP0 = LS.getNDotP0(),
		dSign = StaticPointToStaticLineSegment(Ps, LS) < 0.0f ? -1.0f : 1.0f, // -radius if inside, radius if outside
		nDotPs = Vector3D::Dot(LSNorm, Ps), // n dot Ps
		nDotPe = Vector3D::Dot(LSNorm, Pe), // n dot Pe
		t = (LS.getNDotP0() - Vector3D::Dot(LSNorm, Ps) + (dSign * Radius)) /
		(Vector3D::Dot(LSNorm, v)); // (n dot P0 - n dot Ps + D) / (n dot v)

	collisionPoint = (v * t) + Ps;	// Ps + (v * t)

	if (t > 1.0f ||
		(nDotPs - nDotP0 < -Radius && nDotPe - nDotP0 < -Radius) ||
		(nDotPs - nDotP0 > Radius && nDotPe - nDotP0 > Radius) ||	// Ball will not collide in this iteration
		(Vector3D::Dot(collisionPoint - LS.getP1(), LS.getP0() - LS.getP1()) < 0.0f) ||
		(Vector3D::Dot(collisionPoint - LS.getP0(), LS.getP1() - LS.getP0()) < 0.0f)) // Point of intersection with the infinite line but not finite line
		return -1.0f;

	Pi = collisionPoint;
	return t;
}

float ReflectAnimatedPointOnStaticLineSegment(const Vector3D & Ps, const Vector3D & Pe, const LineSegment3D & LS, Vector3D & Pi, Vector3D & R)
{
	float timeOfIntersection = AnimatedPointToStaticLineSegment(Ps, Pe, LS, Pi);
	if (timeOfIntersection == -1.0f)
		return -1.0f;

	// r = P`e - Pi
	// i = Pe - Pi
	// s = (i dot n) * n
	// m = i - s
	// r = m - s => i - 2s => i - 2(i dot n) * n
	// P`e = Pi + r => Pi + i - 2(i dot n) * n

	Vector3D i = Pe - Pi,
		r = i - ((LS.getNorm() * Vector3D::Dot(i, LS.getNorm())) * 2.0f);
	R = r + Pi;

	return timeOfIntersection;
}

float ReflectAnimatedCircleOnStaticLineSegment(const Vector3D & Ps, const Vector3D & Pe, const float Radius, const LineSegment3D & LS, Vector3D & Pi, Vector3D & R)
{
	float timeOfIntersection = AnimatedCircleToStaticLineSegment(Ps, Pe, Radius, LS, Pi);
	if (timeOfIntersection == -1.0f)
		return -1.0f;

	// r = P`e - Pi
	// i = Pe - Pi
	// s = (i dot n) * n
	// m = i - s
	// r = m - s => i - 2s => i - 2(i dot n) * n
	// P`e = Pi + r => Pi + i - 2(i dot n) * n

	Vector3D i = Pe - Pi,
		r = i - ((LS.getNorm() * Vector3D::Dot(i, LS.getNorm())) * 2.0f);

	R = r + Pi;
	return timeOfIntersection;
}

float AnimatedPointToStaticCircle(const Vector3D & Ps, const Vector3D & Pe, const Vector3D & Center, const float Radius, Vector3D & Pi)
{
	// r' = ARadius
	// r'' = SRadius + ARadius = r + r'
	// s^2 = r''^2 - n^2 => s = sqrt(r''^2 - n^2)
	// v = Pe - Ps
	// m = (Ps - Center) dot (v / |v|)
	// ti0 = (m - s)/ |v|
	// ti1 = (m + s)/ |v|
	// n^2 = |(ACenter0s - SCenter)|^2 - m^2 => n = sqrt(|(ACenterS - SCenter)|^2 - m^2)
	// if ti0 > 1.0f, no collision

	Vector3D SCsubACS = Center - Ps, v = Pe - Ps;
	float vLen = v.Length();

	Vector3D vNorm = v * (1.0f / vLen);

	float m = Vector3D::Dot(SCsubACS, vNorm);
	if (m < 0.0f)
		return -1.0f;

	float SCsubACSLength = SCsubACS.Length(),
		nSquared = SCsubACSLength * SCsubACSLength - m * m,
		sSquared = Radius * Radius - nSquared,
		s = sqrtf(sSquared),
		ti0 = (m - s) / vLen;

	if (ti0 < 0.0f || 1.0f < ti0 || sSquared < 0.0f)
		return -1.0f;

	Vector3D ti0Vec = vNorm * ti0;
	Pi = (vNorm * ti0) + Ps;
	return ti0;
}

float ReflectAnimatedPointOnStaticCircle(const Vector3D & Ps, const Vector3D & Pe, const Vector3D & Center, const float Radius, Vector3D & Pi, Vector3D & R)
{
	float timeOfIntersection = AnimatedPointToStaticCircle(Ps, Pe, Center, Radius, Pi);
	if (timeOfIntersection < 0.0f)
		return -1.0f;

	// n = Center - Pi
	// m = Ps - Pi = u + s
	// u = (m dot n) * n
	// s = Ps - u
	// r = u - s => 2(m dot n) * n - m
	// k = |PsPe|
	// R = Pi + k * rNorm * (1 - timeOfIntersection)

	Vector3D v = Pe - Ps,
		n = Vector3D::Normalize(Center - Pi),
		m = Ps - Pi,
		u = n * Vector3D::Dot(m, n),
		r = Vector3D::Normalize((u * 2.0f) - m) * v.Length();
	R = r * (1.0f - timeOfIntersection);
	return timeOfIntersection;
}

Vector3D ReflectAnimatedPointOnStaticCircle(const Vector3D & Ps, const Vector3D & Pe, const Vector3D & Center, const Vector3D & Pi, const float timeOfIntersection)
{
	Vector3D v = Pe - Ps,
		n = Vector3D::Normalize(Center - Pi),
		m = Ps - Pi,
		u = n * Vector3D::Dot(m, n),
		r = Vector3D::Normalize((u * 2.0f) - m) * v.Length();
	return (r * (1.0f - timeOfIntersection));
}

float AnimatedCircleToStaticCircle(const Vector3D & ACenterS, const Vector3D & ACenterE, const float ARadius, const Vector3D & SCenter, const float SRadius, Vector3D & Pi)
{
	return AnimatedPointToStaticCircle(ACenterS, ACenterE, SCenter, ARadius + SRadius, Pi);
}

float ReflectAnimatedCircleOnStaticCircle(const Vector3D& ACenterS, const Vector3D& ACenterE, const float ARadius, const Vector3D& SCenter, const float SRadius, Vector3D& Pi, Vector3D& R)
{
	return ReflectAnimatedPointOnStaticCircle(ACenterS, ACenterE, SCenter, ARadius + SRadius, Pi, R);
}

Vector3D ReflectAnimatedCircleOnStaticCircle(const Vector3D & ACenterS, const Vector3D & ACenterE, const float ARadius, const Vector3D & SCenter, const Vector3D & Pi, const float timeOfIntersection)
{
	Vector3D v = ACenterE - ACenterS,
		n = Vector3D::Normalize(SCenter - Pi),
		m = ACenterS - Pi,
		u = n * Vector3D::Dot(m, n),
		r = Vector3D::Normalize((u * 2.0f) - m) * v.Length();
	return (r * (1.0f - timeOfIntersection));
}

bool AnimatedCircletoAnimatedCircleWillCollideThisFrame(const Vector3D & CenterS0, const Vector3D & CenterE0, const float Radius0, const Vector3D & CenterS1, const Vector3D & CenterE1, const float Radius1)
{
	float moveRadius0 = (CenterE0 - CenterS0).SquareLength() + (2.f * Radius0 * Radius0);
	float moveRadius1 = (CenterE1 - CenterS1).SquareLength() + (2.f * Radius1 * Radius1);
	float totalRadius = moveRadius0 + moveRadius1;

	float distS0S1 = Vector3D::SquareDistance(CenterS0, CenterS1);
	float distS0E1 = Vector3D::SquareDistance(CenterS0, CenterE1);
	float distE0S1 = Vector3D::SquareDistance(CenterE0, CenterS1);
	float distE0E1 = Vector3D::SquareDistance(CenterE0, CenterE1);

	return (distS0S1 < totalRadius || distS0E1 < totalRadius || distE0S1 < totalRadius || distE0E1 < totalRadius);
}

float AnimatedCircleToAnimatedCircle(const Vector3D & Start0, const Vector3D & End0, const float Radius0, const Vector3D & Start1, const Vector3D & End1, const float Radius1, Vector3D & Pi)
{
	Vector3D v0 = End0 - Start0;
	Vector3D v1 = End1 - Start1;
	float v0Len = v0.Length();
	float v1Len = v1.Length();
	v0 = v0Len != 0.f ? v0 / v0Len : v0;
	v1 = v1Len != 0.f ? v1 / v1Len : v1;
	float t = 0.0f;

	for (t = 0.0f; t <= 1.0f; t += 0.05f) {
		if (StaticCircleToStaticCircle(v0 * (t / v0Len), Radius0, v1 * (t / v1Len), Radius1))
			return t;
	}
	return -1.0f;
}

Vector3D SnapPointStaticCircleToStaticRect(const Vector3D & Circle, const Vector3D & Rect, const float halfWidth, const float halfHeight)
{
	Vector3D snappedPoint = Circle;

	if (snappedPoint.getX() > (Rect.getX() + halfWidth))
		snappedPoint.setX(Rect.getX() + halfWidth);
	else if (snappedPoint.getX() < (Rect.getX() - halfWidth))
		snappedPoint.setX(Rect.getX() - halfWidth);

	if (snappedPoint.getY() > (Rect.getY() + halfHeight))
		snappedPoint.setY(Rect.getY() + halfHeight);
	else if (snappedPoint.getY() < (Rect.getY() - halfHeight))
		snappedPoint.setY(Rect.getY() - halfHeight);

	return snappedPoint;
}

bool StaticCircleToStaticRect(const Vector3D& Circle, const float Radius, const Vector3D& RectCenter, const float halfWidth, const float halfHeight, const Rect3D& rect)
{
	float sqRadius = Radius * Radius;
	Vector3D snappedPoint = SnapPointStaticCircleToStaticRect(Circle, RectCenter, halfWidth, halfHeight);

	if (Vector3D::SquareDistance(Circle, snappedPoint) > sqRadius) // gauranteed no hit
		return false;
	else {
		Rect3D tallRect = rect.StretchHeight(Radius);
		Rect3D wideRect = rect.StretchWidth(Radius);
		float tX, tY;
		
		if (snappedPoint.getX() > RectCenter.getX()) // to the right
			tX = StaticPointToStaticLineSegment(Circle, wideRect.Right());
		else // to the left
			tX = StaticPointToStaticLineSegment(Circle, wideRect.Left());

		if (snappedPoint.getY() > RectCenter.getY()) // above
			tY = StaticPointToStaticLineSegment(Circle, wideRect.Top());
		else // below
			tY = StaticPointToStaticLineSegment(Circle, wideRect.Bottom());

		return tX >= 0.f || tY >= 0.f;
	}
}

bool AnimatedCircleToStaticRectWillCollideThisFrame(const Vector3D & CStart, const Vector3D & CEnd, const float Radius, const Vector3D & RectCenter, const float halfWidth, const float halfHeight, const Rect3D & rect)
{
	Vector3D v0 = CEnd - CStart;
	float v0Len = v0.Length();
	v0 = v0Len != 0.f ? v0 / v0Len : v0;
	float t = 0.0f;
	for (t = 0.0f; t <= 1.0f; t += 0.05f) {
		if (StaticCircleToStaticRect(CStart + (v0 * (t / v0Len)), Radius, RectCenter, halfWidth, halfHeight, rect))
			return true;
	}
	return false;
}

bool AnimatedCircleToAnimatedRectWillCollideThisFrame(const Vector3D & CStart, const Vector3D & CEnd, const float Radius, const Vector3D & RectCenterStart, const Vector3D & RectCenterEnd, const float width, const float height)
{
	Vector3D v0 = CEnd - CStart;
	Vector3D v1 = RectCenterEnd - RectCenterStart;
	float v0Len = v0.Length();
	float v1Len = v1.Length();
	v0 = v0Len != 0.f ? v0 / v0Len : v0;
	v1 = v1Len != 0.f ? v1 / v1Len : v1;
	float t = 0.0f;

	for (t = 0.0f; t <= 1.0f; t += 0.05f) {
		if (StaticRectToStaticCircle(RectCenterStart + (v1 * (t / v1Len)), width, height, CStart + (v0 * (t / v0Len)), Radius))
			return true;
	}
	return false;
}

float AnimatedCircleToAnimatedRect(const Vector3D & Start0, const Vector3D & End0, const float Radius, const Vector3D & Start1, const Vector3D & End1, const float halfWidth, const float halfHeight, Vector3D & Pi)
{
	Vector3D v0 = End0 - Start0; // circle
	Vector3D v1 = End1 - Start1; // rect
	float v0Len = v0.Length();
	float v1Len = v1.Length();
	v0 = v0Len != 0.f ? v0 / v0Len : v0;
	v1 = v1Len != 0.f ? v1 / v1Len : v1;
	float t = 0.0f;

	for (t = 0.0f; t <= 1.0f; t += 0.05f) {
		if (StaticRectToStaticCircle(v1 * (t / v1Len), halfWidth, halfHeight, v0 * (t / v0Len), Radius))
			return t;
	}
	return -1.0f;
}
