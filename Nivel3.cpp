#include "Nivel3.h"
#include "Game.h"
#include "Menu.h"
#include "Ball.h"
#include "Stats.h"
#include "GameOver.h"
#include "Nivel1.h"
#include "Nivel4.h"

Nivel3::Nivel3() {
	
	m_ball.IncrementarVelocidad(4.f); 
	m_ball.setBallMoving(false);
	
	m_stats.IncrementarNivel();	
	
	// Se define una densidad objetivo de bloques
	float targetDensity = 0.5f;
	
	// Se calcula la cantidad total de bloques a colocar
	int totalBlocks = rowCount * columnCount;
	
	// Se calcula la cantidad de bloques que se colocarán según la densidad objetivo
	int numBlocksToPlace = static_cast<int>(targetDensity * totalBlocks);
	
	// Se generan posiciones aleatorias para colocar los bloques
	for (int k = 0; k < numBlocksToPlace; ++k) {
		int randomRow = rand() % rowCount;
		int randomColumn = rand() % columnCount;
		float x = randomColumn * (blockWidth + 6.f) + 5.f;
		float y = randomRow * (blockHeight + 6.f) + 5.f;
		m_blocks.emplace_back(x, y, blockWidth, blockHeight, Color::Yellow);
	}
	
}


void Nivel3::Update(Game &g){
	
	
	if(Keyboard::isKeyPressed(Keyboard::Escape)){
		g.SetScene(new Menu());
		m_ball.setBallMoving(false);
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
	
	for(auto it = m_blocks.begin();it!=m_blocks.end();it++){
		if(m_ball.Colisiona(*it)){
			m_stats.aumentarpuntaje(25);
			m_blocks.erase(it);
			m_ball.Rebotar();
			break;
		}
	}
	
	if(m_ball.falling()){
		m_stats.decrementar_vidas(1);
	}
	
	if(m_stats.VerVidas() == 0){
		m_stats.GuardarScore(m_stats.MostrarPuntajeTotal());
		g.SetScene(new GameOver());
	}
	
	if(m_blocks.empty()){
		g.SetScene(new Nivel4());
		
	}
	
	m_stats.actualizarStats();
	m_ball.Update();
	m_player.Update();
	
}

void Nivel3::Draw(RenderWindow &w){
	w.clear({0,0,0});
	m_ball.Draw(w);
	m_player.Draw(w);
	
	m_stats.DrawStats(w);
	
	for(auto &bloque : m_blocks){
		bloque.Draw(w);
	}
}


