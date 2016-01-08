////////////////////////////////////////////////////////////////////////////////
//
// Paella
// Copyright (C) 2015 - Thomas FORGIONE, Emilie JALRAS, Marion LENFANT, Thierry MALON, Amandine PAILLOUX
// Authors :
//     Thomas FORGIONE
//     Emilie JALRAS
//     Marion LENFANT
//     Thierry MALON
//     Amandine PAILLOUX
//
// This file is part of the project Paella
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
////////////////////////////////////////////////////////////////////////////////
#ifndef VECTOR_FUNCTIONS_HPP
#define VECTOR_FUNCTIONS_HPP

#include <cmath>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>

namespace sft
{

/////////////////////////////////////////////////////////////////
/// \ingroup sfmltools
/// \brief Create vector from origin and destination
/// \param from origin of the new vector
/// \param to destination of the new vector
/// \return to - from
/////////////////////////////////////////////////////////////////
template <class T>
T makeVector(T const& from, T const& to)
{
    return to - from;
}


/////////////////////////////////////////////////////////////////
/// \ingroup sfmltools
/// \brief Computes the dot product between two vectors
/// \param v1 first vector
/// \param v2 second vector
/// \return the value of the dot product between two vectors
/////////////////////////////////////////////////////////////////
template <class T>
auto dotProduct(sf::Vector3<T> const& v1, sf::Vector3<T> const& v2) -> decltype(v1.x)
{
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

/////////////////////////////////////////////////////////////////
/// \ingroup sfmltools
/// \brief Computes the dot product between two vectors
/// \param v1 first vector
/// \param v2 second vector
/// \return the value of the dot product between two vectors
/////////////////////////////////////////////////////////////////
template <class T>
auto dotProduct(sf::Vector2<T> const& v1, sf::Vector2<T> const& v2) -> decltype(v1.x)
{
    return v1.x * v2.x + v1.y * v2.y;
}

/////////////////////////////////////////////////////////////////
/// \ingroup sfmltools
/// \brief Compute the square of the norm of a vector
/// \param vecteur Vector you want to compute the norm of
/// \see norm
/// \return \code dotProduct(vecteur, vecteur) \endcode
///
/// Use this method when you need to compare vector sizes
/////////////////////////////////////////////////////////////////
template <class T>
auto norm2(T const& vecteur) -> decltype(vecteur.x)
{
    return dotProduct(vecteur, vecteur);
}

/////////////////////////////////////////////////////////////////
/// \ingroup sfmltools
/// \brief Compute the norm of a vector
/// \param vecteur Vector you want to compute the norm of
/// \see norm2
/// \return \code std::sqrt(norm2(dotProduct)) \endcode
/////////////////////////////////////////////////////////////////
template <class T>
auto norm(T const& vecteur) -> decltype(vecteur.x)
{
    return std::sqrt(norm2(vecteur));
}

/////////////////////////////////////////////////////////////////
/// \ingroup sfmltools
/// \brief Divides each component of the vector by its norm
/// \param vecteur Vector you want to normalize
/////////////////////////////////////////////////////////////////
template <class T>
void normalize(sf::Vector3<T>& vecteur)
{
    vecteur /= norm(vecteur);
}


/////////////////////////////////////////////////////////////////
/// \ingroup sfmltools
/// \brief Computes the cross product between two Vector3
/// \param v1 first vector of the cross prod
/// \param v2 second vector of the cross prod
/// \return the cross product between the two vectors
/////////////////////////////////////////////////////////////////
template <class T>
sf::Vector3<T> crossProduct(sf::Vector3<T> const& v1, sf::Vector3<T> const& v2)
{
    return sf::Vector3<T>{v1.y * v2.z - v1.z * v2.y,
                          v1.z * v2.x - v1.x * v2.z,
                          v1.x * v2.y - v1.y * v2.x
                         };
}

} // namespace sft

#endif // VECTOR_FUNCTIONS_HPP
