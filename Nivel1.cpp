
#include "Game.h"
#include "Menu.h"
#include <iostream>
#include "Nivel2.h"
#include "GameOver.h"
#include <cmath>
using namespace std;

Nivel1::Nivel1() {
	m_ball.setBallMoving(false);
	m_stats.ResetStats();
	for (int i = 0; i < rowCount; ++i) {
		for (int j = 0; j < columnCount - i; ++j) { /// Ajuste en el límite de columnas
			float x = (j + 0.5f * i) * (blockWidth + 6.f) + 5.f;
			float y = i * (blockHeight + 6.f) + 5.f;
			
			bool isSpecial = (rand () % 20 == 0); /// Probabilidad de 1 / 20 de ser especial el bloque
			if(isSpecial){
				m_blocks.emplace_back(x,y,blockWidth,blockHeight,Color::Yellow,true);
			}else{
				m_blocks.emplace_back(x, y, blockWidth, blockHeight, Color::Red);
			}
		}
	}
}
	

void Nivel1::Update(Game &g){
	
	if(Keyboard::isKeyPressed(Keyboard::Escape)){
		g.SetScene(new Menu());
		m_stats.ResetStats();
	}
	
	if(Keyboard::isKeyPressed(Keyboard::Space)){
		m_ball.setBallMoving(true);
		m_stats.CambiarColores();
		m_stats.draw_text(false);
	}
	
	if(m_ball.Colisiona(m_player)){
		m_ball.Rebotar(m_player.DimensionesPlayer());
	}
	
	
	
	for (auto it = m_blocks.begin(); it != m_blocks.end(); ) {
		if (m_ball.Colisiona(*it)) {
			if (it->isSpecialBlock()) /// Si colisiona con bloque especial pasa esto.. {
				m_stats.aumentarpuntaje(50);
				m_stats.IncrementarVidas();
			} else { /// Si no es especial el bloque pasa esto..
				m_stats.aumentarpuntaje(25);
			}
			m_ball.Rebotar();
			it = m_blocks.erase(it); /// Avanza el iterador después de eliminar el bloque
		} else {
			++it; /// Avanza al siguiente bloque si no hay colisión
		}
	}
	
	if(m_blocks.empty()){
		g.SetScene(new Nivel2());
	}
	
	if(m_ball.falling()){
		m_stats.decrementar_vidas(1);
	}
	
	if(m_stats.VerVidas() == 0){
		m_stats.GuardarScore(m_stats.obtenerpuntaje());
		g.SetScene(new GameOver());
	}
	
	m_stats.actualizarStats();
	m_ball.Update();
	m_player.Update();
	
}

void Nivel1::Draw(RenderWindow &w){
	w.clear({0,0,0});
	m_ball.Draw(w);
	m_player.Draw(w);
	m_stats.DrawStats(w);
	
	for(auto &bloque : m_blocks){
		bloque.Draw(w);
	}
}


