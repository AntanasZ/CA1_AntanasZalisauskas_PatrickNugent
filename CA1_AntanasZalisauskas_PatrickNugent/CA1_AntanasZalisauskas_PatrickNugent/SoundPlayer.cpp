/// <summary>
/// Name: Patrick Nugent
/// Student Number: D00218208
///
/// Name: Antanas Zalisauskas
/// Student Number: D00218148
/// </summary>

#include "SoundPlayer.hpp"
#include "SoundEffect.hpp"

#include <SFML/Audio/Listener.hpp>

#include <cmath>


namespace
{
	// Sound coordinate system, point of view of a player in front of the screen:
	// X = left; Y = up; Z = back (out of the screen)
	const float ListenerZ = 300.f;
	const float Attenuation = 8.f;
	const float MinDistance2D = 200.f;
	const float MinDistance3D = std::sqrt(MinDistance2D * MinDistance2D + ListenerZ * ListenerZ);
}

/// <summary>
/// Edited by: Patrick Nugent
///
///	-Added pickup, button and stun sounds
/// </summary>
SoundPlayer::SoundPlayer()
{
	m_sound_buffers.Load(SoundEffect::kCollectPickup, "Media/Sound/CollectPickup.wav");
	m_sound_buffers.Load(SoundEffect::kButton, "Media/Sound/Button.wav");
	m_sound_buffers.Load(SoundEffect::kStun, "Media/Sound/Stun.wav");

	// Listener points towards the screen (default in SFML)
	sf::Listener::setDirection(0.f, 0.f, -1.f);
}

void SoundPlayer::Play(SoundEffect effect)
{
	Play(effect, GetListenerPosition());
}

void SoundPlayer::Play(SoundEffect effect, sf::Vector2f position)
{
	m_sounds.emplace_back(sf::Sound());
	sf::Sound& sound = m_sounds.back();

	sound.setBuffer(m_sound_buffers.Get(effect));
	sound.setPosition(position.x, -position.y, 0.f);
	sound.setAttenuation(Attenuation);
	sound.setMinDistance(MinDistance3D);

	sound.play();
}

void SoundPlayer::RemoveStoppedSounds()
{
	m_sounds.remove_if([](const sf::Sound& s)
	{
		return s.getStatus() == sf::Sound::Stopped;
	});
}

void SoundPlayer::SetListenerPosition(sf::Vector2f position)
{
	sf::Listener::setPosition(position.x, -position.y, ListenerZ);
}

sf::Vector2f SoundPlayer::GetListenerPosition() const
{
	sf::Vector3f position = sf::Listener::getPosition();
	return sf::Vector2f(position.x, -position.y);
}
