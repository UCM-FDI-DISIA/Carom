#include "GraphicsUtils.h"
#include "PhysicsUtils.h"
#include "SDLUtils.h"
#include <clipper.h>
#include <format>

using namespace Clipper2Lib;


bool GraphisUtils::doPolygonsOverlap(const std::vector<b2Vec2> &verts1, const std::vector<b2Vec2> &verts2, float radius)
{
    // Step 1: Convert Box2D vertices to Clipper2 Paths64
    Paths64 poly1, poly2;
    Path64 path1, path2;

    // Scale factor to convert floating-point (meters) to integers (e.g., millimeters)
    const double scale = 1000.0;

    // Convert verts1 to Path64
    for (const auto& v : verts1) {
        path1.push_back(Point64(v.x * scale, v.y * scale));
    }
    poly1.push_back(path1);

    // Convert verts2 to Path64
    for (const auto& v : verts2) {
        path2.push_back(Point64(v.x * scale, v.y * scale));
    }
    poly2.push_back(path2);

    // Step 2: Offset the polygons to account for Box2D's radius
    // Convert radius to the same scale (e.g., 0.01 meters * 1000 = 10 units)
    double scaledRadius = radius * scale;
    Paths64 offsetPoly1 = InflatePaths(poly1, scaledRadius, JoinType::Round, EndType::Polygon);
    Paths64 offsetPoly2 = InflatePaths(poly2, scaledRadius, JoinType::Round, EndType::Polygon);

    // Step 3: Check for intersection
    Paths64 solution = Intersect(offsetPoly1, offsetPoly2, FillRule::NonZero);

    // Step 4: Return true if they overlap (solution is not empty)
    return !solution.empty();
}

bool GraphisUtils::arePointsInsideArea(const std::vector<b2Vec2> &points, const std::vector<b2Vec2> &area)
{
    Path64 areaPath;
    const double scale = 1000.0;

    for (const auto& v : area) {
        areaPath.push_back(Point64(v.x * scale, v.y * scale));
    }

    for (const auto& p : points) {
        Point64 point(p.x * scale, p.y * scale);

        Clipper2Lib::PointInPolygonResult result = PointInPolygon(point, areaPath);

        if (result == PointInPolygonResult::IsOutside) {
            return false; // If any point is not inside, return false
        }
    }

    // All points are inside if we reach here
    return true;
}

std::vector<uint8_t> GraphisUtils::computeAlphaMask(const std::vector<b2Vec2>& polyVerts, const SDL_Rect& rect, float polyRadius) {
    // Convert the polygon to Clipper2 format
    const double scale = 1000.0; // Scale factor (meters to millimeters)
    Paths64 poly;
    Path64 path;
    for (const auto& v : polyVerts) {
        path.push_back(Point64(v.x * scale, v.y * scale));
    }
    poly.push_back(path);

    // Offset the polygon to account for Box2D's radius
    double scaledRadius = polyRadius * scale; // e.g., 0.01 meters * 1000 = 10
    Paths64 offsetPoly = InflatePaths(poly, scaledRadius, JoinType::Round, EndType::Polygon);

    // Ensure offsetPoly has at least one polygon
    if (offsetPoly.empty()) {
        // If offsetPoly is empty, return a fully transparent mask
        return std::vector<uint8_t>(rect.w * rect.h, 0);
    }

    // Take the first polygon from offsetPoly (should typically be just one for simple offsetting)
    const Path64& basePoly = offsetPoly[0];

    // Compute pixel distances in Clipper2's scaled coordinates
    const float pixelsPerMeter = PhysicsConverter::PIXELS_PER_METER; // Use the correct scale
    const float metersPerPixel = 1.0f / pixelsPerMeter; // e.g., 1 pixel = 0.01 meters if PIXELS_PER_METER = 100
    const double scaledDistance1Pixel = 1.0 * metersPerPixel * scale; // 1 pixel in scaled coordinates
    const double scaledDistance2Pixels = 2.0 * metersPerPixel * scale; // 2 pixels
    const double scaledDistance3Pixels = 3.0 * metersPerPixel * scale; // 3 pixels
    const double scaledDistance4Pixels = 4.0 * metersPerPixel * scale; // 4 pixels
    const double scaledDistance5Pixels = 5.0 * metersPerPixel * scale; // 5 pixels
    const double scaledDistance6Pixels = 6.0 * metersPerPixel * scale; // 6 pixels
    const double scaledDistance7Pixels = 7.0 * metersPerPixel * scale; // 7 pixels
    const double scaledDistance8Pixels = 8.0 * metersPerPixel * scale; // 8 pixels
    const double scaledDistance9Pixels = 9.0 * metersPerPixel * scale; // 9 pixels
    const double scaledDistance10Pixels = 10.0 * metersPerPixel * scale; // 10 pixels

    // Offset the polygon at different distances (inward)
    Paths64 innerPoly1 = InflatePaths(offsetPoly, -scaledDistance1Pixel, JoinType::Round, EndType::Polygon);   // -1 pixel: alpha = 50
    Paths64 innerPoly2 = InflatePaths(offsetPoly, -scaledDistance2Pixels, JoinType::Round, EndType::Polygon);  // -2 pixels: alpha = 75
    Paths64 innerPoly3 = InflatePaths(offsetPoly, -scaledDistance3Pixels, JoinType::Round, EndType::Polygon);  // -3 pixels: alpha = 100
    Paths64 innerPoly4 = InflatePaths(offsetPoly, -scaledDistance4Pixels, JoinType::Round, EndType::Polygon);  // -4 pixels: alpha = 125
    Paths64 innerPoly5 = InflatePaths(offsetPoly, -scaledDistance5Pixels, JoinType::Round, EndType::Polygon);  // -5 pixels: alpha = 150
    Paths64 innerPoly6 = InflatePaths(offsetPoly, -scaledDistance6Pixels, JoinType::Round, EndType::Polygon);  // -6 pixels: alpha = 175
    Paths64 innerPoly7 = InflatePaths(offsetPoly, -scaledDistance7Pixels, JoinType::Round, EndType::Polygon);  // -7 pixels: alpha = 200
    Paths64 innerPoly8 = InflatePaths(offsetPoly, -scaledDistance8Pixels, JoinType::Round, EndType::Polygon);  // -8 pixels: alpha = 225
    Paths64 innerPoly9 = InflatePaths(offsetPoly, -scaledDistance9Pixels, JoinType::Round, EndType::Polygon);  // -9 pixels: alpha = 250
    Paths64 innerPoly10 = InflatePaths(offsetPoly, -scaledDistance10Pixels, JoinType::Round, EndType::Polygon); // -10 pixels: alpha = 255

    // Ensure the offset polygons are not empty
    const Path64* innerPath1 = innerPoly1.empty() ? nullptr : &innerPoly1[0];
    const Path64* innerPath2 = innerPoly2.empty() ? nullptr : &innerPoly2[0];
    const Path64* innerPath3 = innerPoly3.empty() ? nullptr : &innerPoly3[0];
    const Path64* innerPath4 = innerPoly4.empty() ? nullptr : &innerPoly4[0];
    const Path64* innerPath5 = innerPoly5.empty() ? nullptr : &innerPoly5[0];
    const Path64* innerPath6 = innerPoly6.empty() ? nullptr : &innerPoly6[0];
    const Path64* innerPath7 = innerPoly7.empty() ? nullptr : &innerPoly7[0];
    const Path64* innerPath8 = innerPoly8.empty() ? nullptr : &innerPoly8[0];
    const Path64* innerPath9 = innerPoly9.empty() ? nullptr : &innerPoly9[0];
    const Path64* innerPath10 = innerPoly10.empty() ? nullptr : &innerPoly10[0];

    // Offset the polygon at 1 pixel outward for antialiasing
    Paths64 outerPoly1 = InflatePaths(offsetPoly, scaledDistance1Pixel, JoinType::Round, EndType::Polygon);
    const Path64& outerPath1 = outerPoly1.empty() ? basePoly : outerPoly1[0];

    // Create the alpha mask (rect.w * rect.h elements)
    std::vector<uint8_t> alphaMask(rect.w * rect.h, 0); // Initialize all to 0 (transparent)

    // First pass: Classify pixels and assign alpha values
    for (int y = 0; y < rect.h; ++y) {
        for (int x = 0; x < rect.w; ++x) {
            // Pixel coordinates in the texture (relative to the top-left of the rect)
            int px = rect.x + x;
            int py = rect.y + y;

            // Convert pixel coordinates to meters
            b2Vec2 point = PhysicsConverter::pixel2meter(px, py);

            // Convert the point to Clipper2's scaled coordinates
            Point64 pt(point.x * scale, point.y * scale);

            // Check if the point is inside, on, or outside the base polygon
            PointInPolygonResult resultBase = PointInPolygon(pt, basePoly);
            bool isInsideBase = (resultBase == PointInPolygonResult::IsInside || resultBase == PointInPolygonResult::IsOn);

            if (!isInsideBase) {
                // Outside the base polygon: check for antialiasing
                PointInPolygonResult resultOuter1 = PointInPolygon(pt, outerPath1);
                if (resultOuter1 == PointInPolygonResult::IsInside || resultOuter1 == PointInPolygonResult::IsOn) {
                    // Between the border and 1 pixel outward: compute distance for antialiasing
                    double minDistance = 0.0; // Distance from the border (in scaled coordinates)
                    bool found = false;
                    const double step = scaledDistance1Pixel / 2.0; // Check every 0.5 pixels
                    for (double offset = 0.0; offset <= scaledDistance1Pixel; offset += step) {
                        Paths64 testPoly = InflatePaths(offsetPoly, offset, JoinType::Round, EndType::Polygon);
                        if (testPoly.empty()) continue;
                        PointInPolygonResult result = PointInPolygon(pt, testPoly[0]);
                        if (result == PointInPolygonResult::IsOn || result == PointInPolygonResult::IsInside) {
                            minDistance = offset;
                            found = true;
                            break;
                        }
                    }

                    if (!found) {
                        // If we didn't find the distance, assume it's just outside the border
                        minDistance = 0.0;
                    }

                    // Linearly interpolate alpha from 0 (1 pixel outside) to 25 (at the border)
                    double alphaFactor = 1.0 - (minDistance / scaledDistance1Pixel); // 1.0 at border, 0.0 at 1 pixel outside
                    alphaFactor = std::clamp(alphaFactor, 0.0, 1.0);
                    double alpha = 0.0 + (25.0 - 0.0) * alphaFactor;
                    alphaMask[y * rect.w + x] = static_cast<uint8_t>(std::round(alpha));
                } else {
                    // Beyond 1 pixel outward: fully transparent
                    alphaMask[y * rect.w + x] = 0;
                }
            } else {
                // Inside the base polygon: apply the inward transition
                if (innerPath10 && (PointInPolygon(pt, *innerPath10) == PointInPolygonResult::IsInside || PointInPolygon(pt, *innerPath10) == PointInPolygonResult::IsOn)) {
                    // 10 pixels inward or deeper: fully opaque
                    alphaMask[y * rect.w + x] = 255;
                } else if (innerPath9 && (PointInPolygon(pt, *innerPath9) == PointInPolygonResult::IsInside || PointInPolygon(pt, *innerPath9) == PointInPolygonResult::IsOn)) {
                    // Between 9 and 10 pixels inward
                    alphaMask[y * rect.w + x] = 250; // 9 pixels inward: alpha = 250
                } else if (innerPath8 && (PointInPolygon(pt, *innerPath8) == PointInPolygonResult::IsInside || PointInPolygon(pt, *innerPath8) == PointInPolygonResult::IsOn)) {
                    // Between 8 and 9 pixels inward
                    alphaMask[y * rect.w + x] = 225; // 8 pixels inward: alpha = 225
                } else if (innerPath7 && (PointInPolygon(pt, *innerPath7) == PointInPolygonResult::IsInside || PointInPolygon(pt, *innerPath7) == PointInPolygonResult::IsOn)) {
                    // Between 7 and 8 pixels inward
                    alphaMask[y * rect.w + x] = 200; // 7 pixels inward: alpha = 200
                } else if (innerPath6 && (PointInPolygon(pt, *innerPath6) == PointInPolygonResult::IsInside || PointInPolygon(pt, *innerPath6) == PointInPolygonResult::IsOn)) {
                    // Between 6 and 7 pixels inward
                    alphaMask[y * rect.w + x] = 175; // 6 pixels inward: alpha = 175
                } else if (innerPath5 && (PointInPolygon(pt, *innerPath5) == PointInPolygonResult::IsInside || PointInPolygon(pt, *innerPath5) == PointInPolygonResult::IsOn)) {
                    // Between 5 and 6 pixels inward
                    alphaMask[y * rect.w + x] = 150; // 5 pixels inward: alpha = 150
                } else if (innerPath4 && (PointInPolygon(pt, *innerPath4) == PointInPolygonResult::IsInside || PointInPolygon(pt, *innerPath4) == PointInPolygonResult::IsOn)) {
                    // Between 4 and 5 pixels inward
                    alphaMask[y * rect.w + x] = 125; // 4 pixels inward: alpha = 125
                } else if (innerPath3 && (PointInPolygon(pt, *innerPath3) == PointInPolygonResult::IsInside || PointInPolygon(pt, *innerPath3) == PointInPolygonResult::IsOn)) {
                    // Between 3 and 4 pixels inward
                    alphaMask[y * rect.w + x] = 100; // 3 pixels inward: alpha = 100
                } else if (innerPath2 && (PointInPolygon(pt, *innerPath2) == PointInPolygonResult::IsInside || PointInPolygon(pt, *innerPath2) == PointInPolygonResult::IsOn)) {
                    // Between 2 and 3 pixels inward
                    alphaMask[y * rect.w + x] = 75; // 2 pixels inward: alpha = 75
                } else if (innerPath1 && (PointInPolygon(pt, *innerPath1) == PointInPolygonResult::IsInside || PointInPolygon(pt, *innerPath1) == PointInPolygonResult::IsOn)) {
                    // Between 1 and 2 pixels inward
                    alphaMask[y * rect.w + x] = 50; // 1 pixel inward: alpha = 50
                } else {
                    // Between the border and 1 pixel inward
                    alphaMask[y * rect.w + x] = 50; // Default to 50 if innerPath1 is empty
                }
            }
        }
    }

    // Second pass: Set the border pixels to alpha = 25
    for (int y = 0; y < rect.h; ++y) {
        for (int x = 0; x < rect.w; ++x) {
            // Pixel coordinates in the texture (relative to the top-left of the rect)
            int px = rect.x + x;
            int py = rect.y + y;

            // Convert pixel coordinates to meters
            b2Vec2 point = PhysicsConverter::pixel2meter(px, py);

            // Convert the point to Clipper2's scaled coordinates
            Point64 pt(point.x * scale, point.y * scale);

            // Check if the point is on the border
            PointInPolygonResult resultBase = PointInPolygon(pt, basePoly);
            if (resultBase == PointInPolygonResult::IsOn) {
                alphaMask[y * rect.w + x] = 25; // On the border: alpha = 25
            }
        }
    }

    return alphaMask;
}

std::vector<std::vector<b2Vec2>> 
GraphisUtils::generateNonOverlappingPolygons(
    float minRadius, float maxRadius, 
    int n, int m, 
    float areaX, float areaY, 
    float areaW, float areaH,
    RNG_Manager* rng) 
{
    std::vector<std::vector<b2Vec2>> polygons;
    
    int attempts = 0;
    const int maxAttempts = 100; // Prevent infinite loops
    
    while (polygons.size() < n && attempts < maxAttempts) {
        // Step 1: Choose random center
        float cx = rng->randomRange(areaX, areaX + areaW);
        float cy = rng->randomRange(areaY, areaY + areaH);
        
        // Step 2: Choose random radius and radius range
        float polyRadius = rng->randomRange(minRadius, maxRadius);
        float radiusRange = polyRadius * 0.35f;
        
        // Generate initial polygon vertices
        std::vector<b2Vec2> vertices;
        float angleStep = (2 * M_PI) / m;
        
        for (int i = 0; i < m; i++) {
            float angle = i * angleStep;
            // Calculate random radius within range
            float radius = rng->randomRange(
                polyRadius - radiusRange/2, 
                polyRadius + radiusRange/2
            );
            
            // Calculate point position in pixels
            float x = cx + radius * cos(angle);
            float y = cy + radius * sin(angle);
            
            // Convert to meters before adding
            b2Vec2 vertex = PhysicsConverter::pixel2meter(x, y);
            vertices.push_back(vertex);
        }
        
        // Compute the convex hull to ensure the shape is valid for Box2D
        b2Hull hull = b2ComputeHull(vertices.data(), vertices.size());
        if (!b2ValidateHull(&hull)) {
            attempts++;
            // std::cout << "Invalid hull" << std::endl;
            continue; // Skip this polygon if the hull is invalid
        }
        
        // Create a new vertex list from the hull
        std::vector<b2Vec2> convexVertices;
        for (int i = 0; i < hull.count; i++) {
            convexVertices.push_back(hull.points[i]);
        }
        
        // Check for overlap with existing polygons
        bool overlaps = false;
        for (const auto& existingPoly : polygons) {
            if (GraphisUtils::doPolygonsOverlap(convexVertices, existingPoly)) {
                overlaps = true;
                break;
            }
        }
        
        // If no overlap, add the polygon
        if (!overlaps) {
            polygons.push_back(convexVertices);
            attempts = 0; // Reset attempts counter
        } else {
            attempts++;
        }
        // std::cout << "Attempts: " << attempts << std::endl;
    }
    
    return polygons;
}

std::pair<std::vector<SDL_Rect>, std::vector<b2Vec2>>
GraphisUtils::generatePolygonBoundingBoxes(const std::vector<std::vector<b2Vec2>>& polygons, 
    int areaPosX, int areaPosY, 
    int areaWidth, int areaHeight) 
{
    std::vector<SDL_Rect> boundingBoxes;
    std::vector<b2Vec2> unclampedCenters;
    boundingBoxes.reserve(polygons.size());
    unclampedCenters.reserve(polygons.size());

    const float polyRadius = 0.01f; // Match the radius used in doPolygonsOverlap and computeAlphaMask
    const int radiusPixels = PhysicsConverter::meter2pixel(polyRadius);

    for (const auto& polygon : polygons) {
        auto [firstX, firstY] = PhysicsConverter::meter2pixel(polygon[0]);
        int minX = firstX;
        int maxX = firstX;
        int minY = firstY;
        int maxY = firstY;

        // Compute the min and max coordinates of the polygon in pixels
        for (size_t i = 1; i < polygon.size(); i++) {
            auto [x, y] = PhysicsConverter::meter2pixel(polygon[i]);
            minX = std::min(minX, x);
            maxX = std::max(maxX, x);
            minY = std::min(minY, y);
            maxY = std::max(maxY, y);
        }

        // Expand the bounding box by the radius to account for Box2D's polygon radius
        minX -= radiusPixels;
        maxX += radiusPixels;
        minY -= radiusPixels;
        maxY += radiusPixels;

        // Compute the center of the unclamped bounding box in pixels
        float unclampedCenterX = minX + (maxX - minX) / 2.0f;
        float unclampedCenterY = minY + (maxY - minY) / 2.0f;

        // Convert the unclamped center to meters
        b2Vec2 unclampedCenter = PhysicsConverter::pixel2meter(unclampedCenterX, unclampedCenterY);
        unclampedCenters.push_back(unclampedCenter);

        // Now apply clamping to the bounding box to get the SDL_Rect
        // Clamp the bounding box to the area boundaries
        minX = std::max(minX, areaPosX);
        minY = std::max(minY, areaPosY);
        maxX = std::min(maxX, areaPosX + areaWidth);
        maxY = std::min(maxY, areaPosY + areaHeight);

        // Recompute width and height after clamping
        int width = maxX - minX;
        int height = maxY - minY;

        // Ensure width and height are non-negative
        width = std::max(width, 0);
        height = std::max(height, 0);

        // Create the SDL_Rect
        SDL_Rect rect;
        rect.x = minX;
        rect.y = minY;
        rect.w = width;
        rect.h = height;

        boundingBoxes.push_back(rect);
    }

    return {boundingBoxes, unclampedCenters};
}

b2Vec2 GraphisUtils::calculatePolygonCenter(const std::vector<b2Vec2> &polygon)
{
    b2Vec2 polyCenter;

    auto [firstX, firstY] = polygon[0];
    int minX = firstX;
    int maxX = firstX;
    int minY = firstY;
    int maxY = firstY;

    // Compute the min and max coordinates of the polygon in pixels
    for (size_t i = 1; i < polygon.size(); i++) {
        minX = std::min(minX, (int)polygon[i].x);
        maxX = std::max(maxX, (int)polygon[i].x);
        minY = std::min(minY, (int)polygon[i].y);
        maxY = std::max(maxY, (int)polygon[i].y);
    }

    // Compute the center in pixels
    float centerX = minX + (maxX - minX) / 2.0f;
    float centerY = minY + (maxY - minY) / 2.0f;
    polyCenter = {centerX, centerY};

    return polyCenter;
}


// TOP LEFT en coord abs
// Orginal rect in absolute x, y
// Returns partial rect in local coordinates respect to original
SDL_Rect GraphisUtils::generatePartialRect(SDL_Rect originalRect, SDL_Rect areaConstrain)
{
    int x = originalRect.x;
    int y = originalRect.y;
    int w = originalRect.w;
    int h = originalRect.h;
    
    // min and max in absolute
    int minX = x;
    int maxX = x + w;
    int minY = y;
    int maxY = y + h;

    // SDL_Rect
    minX = std::max(minX, areaConstrain.x);
    minY = std::max(minY, areaConstrain.y);
    maxX = std::min(maxX, areaConstrain.x + areaConstrain.w);
    maxY = std::min(maxY, areaConstrain.y + areaConstrain.h);

    // Compute width and height after clamping
    int width = maxX - minX;
    int height = maxY - minY;

    // Ensure width and height are non-negative
    width = std::max(width, 0);
    height = std::max(height, 0);

    // Offset of partial to original rect
    // Create the SDL_Rect in LOCAL coordinates
    SDL_Rect rect;
    rect.x = minX - originalRect.x;
    rect.y = minY - originalRect.y;
    rect.w = width;
    rect.h = height;

    return rect;
}

// (x,y) from rect absolute coordinates to the screen
SDL_Rect GraphisUtils::getTopLeftRect(IntPair center, IntPair size)
{
    return {center.first - size.first/2, center.second - size.second/2, size.first, size.second};
}


SDL_Rect GraphisUtils::getCenterRect(IntPair pos, IntPair size)
{
    return {pos.first + size.first/2, pos.second + size.second/2, size.first, size.second};
}

SDL_Rect GraphisUtils::getCenterRect(const SDL_Rect &topleftRect)
{
    return {topleftRect.x + topleftRect.w/2, topleftRect.y + topleftRect.h/2, topleftRect.w, topleftRect.h};
}

// Everything in pixels: in and out
std::pair<SDL_Rect, b2Vec2> GraphisUtils::generatePolygonBoundingBox(const std::vector<b2Vec2> &polygon, int areaPosX, int areaPosY, int areaWidth, int areaHeight)
{
    SDL_Rect boundingBox;
    b2Vec2 unclampedCenter;

    auto [firstX, firstY] = polygon[0];
    int minX = firstX;
    int maxX = firstX;
    int minY = firstY;
    int maxY = firstY;

    // Compute the min and max coordinates of the polygon in pixels
    for (size_t i = 1; i < polygon.size(); i++) {
        minX = std::min(minX, (int)polygon[i].x);
        maxX = std::max(maxX, (int)polygon[i].x);
        minY = std::min(minY, (int)polygon[i].y);
        maxY = std::max(maxY, (int)polygon[i].y);
    }

    // Compute the center of the unclamped bounding box in pixels
    float unclampedCenterX = minX + (maxX - minX) / 2.0f;
    float unclampedCenterY = minY + (maxY - minY) / 2.0f;
    unclampedCenter = {unclampedCenterX, unclampedCenterY};

    // Now apply clamping to the bounding box to get the SDL_Rect
    // Clamp the bounding box to the area boundaries
    // Pixels
    minX = std::max(minX, areaPosX);
    minY = std::max(minY, areaPosY);
    maxX = std::min(maxX, areaPosX + areaWidth);
    maxY = std::min(maxY, areaPosY + areaHeight);

    // Recompute width and height after clamping
    int width = maxX - minX;
    int height = maxY - minY;

    // Ensure width and height are non-negative
    width = std::max(width, 0);
    height = std::max(height, 0);

    // Create the SDL_Rect
    SDL_Rect rect;
    rect.x = minX;
    rect.y = minY;
    rect.w = width;
    rect.h = height;

    boundingBox = rect;

    return {boundingBox, unclampedCenter};
}

std::vector<b2Vec2> GraphisUtils::sdlrectToPolygon(const SDL_Rect &rect)
{
    std::vector<b2Vec2> polygon;

    polygon.push_back({static_cast<float>(rect.x), static_cast<float>(rect.y)});
    polygon.push_back({static_cast<float>(rect.x + rect.w), static_cast<float>(rect.y)});
    polygon.push_back({static_cast<float>(rect.x + rect.w), static_cast<float>(rect.y + rect.h)});
    polygon.push_back({static_cast<float>(rect.x), static_cast<float>(rect.y + rect.h)});

    return polygon;
}

// On pixels
std::vector<std::vector<b2Vec2>> GraphisUtils::extractPolygons(int n, int vert)
{
    auto svg = &sdlutils().svgs().at("grp_arena");
    std::vector<std::vector<b2Vec2>> polygons;
    polygons.reserve(n);

    char idx = 'a';

    for (int i = 0; i < n; ++i)
    {
        std::vector<b2Vec2> vertices;

        for (int j = 1; j <= vert; ++j)
        {
            std::string str = std::string(1, idx);

            b2Vec2 vert = {(float)svg->at(str + std::to_string(j)).x, (float)svg->at(str + std::to_string(j)).y};

            vertices.push_back(vert);
        }
        polygons.push_back(vertices);
        idx += 1;
    }

    // for (auto& p : polygons){
    //     for (auto& v : vertices){
    //         std::cout << "vertice: " << v.x << " " << v.y << std::endl;
    //     }
    // }

    // std::cout << "polygons: " << polygons.size() << std::endl;

    return polygons;
}

std::vector<b2Vec2> GraphisUtils::extractPointsFromSVG(int n, int startIdx, const std::string& name, const std::string& group)
{
    auto svg = &sdlutils().svgs().at(group);
    std::vector<b2Vec2> points;
    points.reserve(n);

    std::cout << "name: " << name << std::endl;

    for (int i = startIdx; i < n + startIdx; ++i)
    {
        std::cout << "point: " << name + std::to_string(i) << std::endl;

        b2Vec2 point = {static_cast<float>(svg->at(name + std::to_string(i)).x)
                     ,  static_cast<float>(svg->at(name + std::to_string(i)).y)
                    };

        points.push_back(point);
    }

    return points;
}

void GraphisUtils::coutRect(const SDL_Rect &rect)
{
    std::cout << "Rect x: " << rect.x << ", y: " << rect.y << ", w: " << rect.w << ", h: " << rect.h << std::endl;
}
