<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="2.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:output method="html" version="5.0"/>
<xsl:include href="weather.xsl"/>

<xsl:template match="/">
<link rel="stylesheet" type="text/css" href="weather-1.css"/>

<html>
<body>
	<!-- ACT & NSW -->
	<div class="region">
		<div class="regionheading">
			<h1>NSW and ACT Forecast</h1>
		</div>	

		<xsl:for-each select="product/forecast/area/forecast-period/text">
			<xsl:if test="@type='synoptic_situation'">
				<div class="overview">
					<xsl:value-of select="text()"/>
				</div>
			</xsl:if>  
		</xsl:for-each>
		
		<!-- canberra -->
		<div class="city">
			<div class="cityheading">
				<h2>Canberra</h2>
			</div>
			
			<div class="info">
				<xsl:for-each select="$data3/product/forecast/area">
					<xsl:if test="@description='Canberra'">
						<xsl:for-each select="forecast-period">
							<!-- grab the first 3 days -->
							<xsl:if test="number(@index) &lt; 3">
								<xsl:variable name="data3index" select="number(@index)"/>
								<div class="days">
									<!-- get date with formatting -->
									<div class="datetime">
										<xsl:variable name="issue-time-local" select="$data3/product/amoc/issue-time-local"/>
										<xsl:text>Forecast for </xsl:text>
										<xsl:if test="format-dateTime($issue-time-local, '[Y0001]-[M01]-[D01]')=format-dateTime(@start-time-local, '[Y0001]-[M01]-[D01]')">
											<xsl:text>the rest of </xsl:text>
										</xsl:if>
										<xsl:value-of select="format-dateTime(@start-time-local, '[FNn], [D1o] [MNn]')"/>
									</div>
									
									<!-- get description forecast -->
									<xsl:for-each select="$data2/product/forecast/area">
										<xsl:if test="@description='Canberra'">
											<xsl:for-each select="forecast-period">
												<xsl:if test="number(@index)=$data3index">
													<xsl:for-each select="text">
														<xsl:if test="@type='forecast'">
															<div class="description">
																<xsl:value-of select="text()"/>
															</div>
														</xsl:if>										
													</xsl:for-each>
												</xsl:if>
											</xsl:for-each>
										</xsl:if>
									</xsl:for-each>
									
									<table>
										<tr>
											<!-- min/max values -->
											<xsl:for-each select="element">
												
												<xsl:if test="@type='air_temperature_minimum'">
													<td>
														<div class="min">
															<xsl:text>Min </xsl:text>
															<xsl:value-of select="text()"/>
														</div>
													</td>
												</xsl:if>
												
												<xsl:if test="@type='air_temperature_maximum'">
													<td>
														<div class="max">
															<xsl:text>Max </xsl:text>
															<xsl:value-of select="text()"/>
														</div>
													</td>
												</xsl:if>
											</xsl:for-each>
										</tr>
									</table>
									
									<!-- rain percentage -->
									<xsl:for-each select="text">
										<xsl:if test="@type='probability_of_precipitation'">
											<div class="rain">
												<xsl:text>Rain </xsl:text>
												<xsl:value-of select="text()"/>
											</div>
										</xsl:if>										
									</xsl:for-each>
								</div>
								<br></br>
							</xsl:if>  
						</xsl:for-each>
					</xsl:if>  
				</xsl:for-each>
			</div>
		</div>
		<!-- canberra -->
		
		<!-- sydney -->
		<div class="city">
			<div class="cityheading">
				<h2>Sydney</h2>
			</div>
			
			<div class="info">
				<xsl:for-each select="$data3/product/forecast/area">
					<xsl:if test="@description='Sydney'">
						<xsl:for-each select="forecast-period">
							<!-- grab the first 3 days -->
							<xsl:if test="number(@index) &lt; 3">
								<xsl:variable name="data3index" select="number(@index)"/>
								<div class="days">
									<!-- get date with formatting -->
									<div class="datetime">
										<xsl:variable name="issue-time-local" select="$data3/product/amoc/issue-time-local"/>
										<xsl:text>Forecast for </xsl:text>
										<xsl:if test="format-dateTime($issue-time-local, '[Y0001]-[M01]-[D01]')=format-dateTime(@start-time-local, '[Y0001]-[M01]-[D01]')">
											<xsl:text>the rest of </xsl:text>
										</xsl:if>
										<xsl:value-of select="format-dateTime(@start-time-local, '[FNn], [D1o] [MNn]')"/>
									</div>
									
									<!-- get description forecast -->
									<xsl:for-each select="$data2/product/forecast/area">
										<xsl:if test="@description='Sydney'">
											<xsl:for-each select="forecast-period">
												<xsl:if test="number(@index)=$data3index">
													<xsl:for-each select="text">
														<xsl:if test="@type='forecast'">
															<div class="description">
																<xsl:value-of select="text()"/>
															</div>
														</xsl:if>										
													</xsl:for-each>
												</xsl:if>
											</xsl:for-each>
										</xsl:if>
									</xsl:for-each>
									
									<table>
									<tr>
									<!-- min/max values -->
									<xsl:for-each select="element">
										
										<xsl:if test="@type='air_temperature_minimum'">
											<td>
												<div class="min">
													<xsl:text>Min </xsl:text>
													<xsl:value-of select="text()"/>
												</div>
											</td>
										</xsl:if>
										
										<xsl:if test="@type='air_temperature_maximum'">
											<td>
												<div class="max">
													<xsl:text>Max </xsl:text>
													<xsl:value-of select="text()"/>
												</div>
											</td>
										</xsl:if>
										
									</xsl:for-each>
									</tr>
									</table>
									
									<!-- rain percentage -->
									<xsl:for-each select="text">
										<xsl:if test="@type='probability_of_precipitation'">
											<div class="rain">
												<xsl:text>Rain </xsl:text>
												<xsl:value-of select="text()"/>
											</div>
										</xsl:if>										
									</xsl:for-each>
								</div>
								<br></br>
							</xsl:if>  
						</xsl:for-each>
					</xsl:if>  
				</xsl:for-each>
			</div>
		</div><!-- sydney -->
	</div><!-- ACT & NSW -->
	
	<!-- VIC REGION -->
	<div class="region">
		<div class="regionheading">
			<h1>Victoria State Forecast</h1>
		</div>	
		
		<xsl:for-each select="$data4/product/forecast/area/forecast-period/text">
			<xsl:if test="@type='synoptic_situation'">
				<div class="overview">
					<xsl:value-of select="text()"/>
				</div>
			</xsl:if>  
		</xsl:for-each>
		
		<!-- melbourne -->
		<div class="city">
			<div class="cityheading">
				<h2>Melbourne</h2>
			</div>
			
			<div class="info">
				<xsl:for-each select="$data6/product/forecast/area">
					<xsl:if test="@description='Melbourne'">
						<xsl:for-each select="forecast-period">
							<!-- grab the first 3 days -->
							<xsl:if test="number(@index) &lt; 3">
								<xsl:variable name="data6index" select="number(@index)"/>
								<div class="days">
									<!-- get date with formatting -->
									<div class="datetime">
										<xsl:variable name="issue-time-local" select="$data6/product/amoc/issue-time-local"/>
										<xsl:text>Forecast for </xsl:text>
										<xsl:if test="format-dateTime($issue-time-local, '[Y0001]-[M01]-[D01]')=format-dateTime(@start-time-local, '[Y0001]-[M01]-[D01]')">
											<xsl:text>the rest of </xsl:text>
										</xsl:if>
										<xsl:value-of select="format-dateTime(@start-time-local, '[FNn], [D1o] [MNn]')"/>
									</div>
									
									<!-- get description forecast -->
									<xsl:for-each select="$data5/product/forecast/area">
										<xsl:if test="@description='Melbourne'">
											<xsl:for-each select="forecast-period">
												<xsl:if test="number(@index)=$data6index">
													<xsl:for-each select="text">
														<xsl:if test="@type='forecast'">
															<div class="description">
																<xsl:value-of select="text()"/>
															</div>
														</xsl:if>										
													</xsl:for-each>
												</xsl:if>
											</xsl:for-each>
										</xsl:if>
									</xsl:for-each>
									
									<table>
										<tr>
											<!-- min/max values -->
											<xsl:for-each select="element">
												
												<xsl:if test="@type='air_temperature_minimum'">
													<td>
														<div class="min">
															<xsl:text>Min </xsl:text>
															<xsl:value-of select="text()"/>
														</div>
													</td>
												</xsl:if>
												
												<xsl:if test="@type='air_temperature_maximum'">
													<td>
														<div class="max">
															<xsl:text>Max </xsl:text>
															<xsl:value-of select="text()"/>
														</div>
													</td>
												</xsl:if>
												
											</xsl:for-each>
										</tr>
									</table>
									
									<!-- rain percentage -->
									<xsl:for-each select="text">
										<xsl:if test="@type='probability_of_precipitation'">
											<div class="rain">
												<xsl:text>Rain </xsl:text>
												<xsl:value-of select="text()"/>
											</div>
										</xsl:if>										
									</xsl:for-each>
								</div>
							</xsl:if>
							<br></br>
						</xsl:for-each>
					</xsl:if>  
				</xsl:for-each>
			</div>
		</div><!-- melbourne -->
	</div><!-- VIC REGION -->
	
	<!-- Snowy Mountain District -->
	<div class="region">
		<div class="regionheading">
			<h1>Snowy Mountain District Forecast</h1>
		</div>	
		
		<xsl:for-each select="$data1/product/forecast/area/forecast-period/text">
			<xsl:if test="@type='synoptic_situation'">
				<div class="overview">
					<xsl:value-of select="text()"/>
				</div>
			</xsl:if>  
		</xsl:for-each>
		
		
		<div class="smdDay"><!-- Day 1 -->
			<!-- get date with formatting -->
			<div class="datetime">
				<xsl:variable name="issue-time" select="$data1/product/amoc/issue-time-local"/>
				<xsl:for-each select="$data1/product/forecast/area">
					<xsl:if test="@description='Jindabyne'">
						<xsl:for-each select="forecast-period">
							<xsl:if test="number(@index) = 0">
								<xsl:variable name="start-time" select="@start-time-local"/>
								
								<xsl:text>Forecast for </xsl:text>
								
								<xsl:if test="format-dateTime($issue-time, '[Y0001]-[M01]-[D01]')=format-dateTime($start-time, '[Y0001]-[M01]-[D01]')">
									<xsl:text>the rest of </xsl:text>
								</xsl:if>
								
								<xsl:value-of select="format-dateTime($start-time, '[FNn], [D1o] [MNn]')"/>
							</xsl:if>
						</xsl:for-each>
					</xsl:if>
				</xsl:for-each>
			</div>
			
			
			<table class="smdT">
			<!-- Jindabyne 1 -->
			<tr>
			<div class="area">
				<xsl:for-each select="$data1/product/forecast/area">
					<xsl:if test="@description='Jindabyne'">
						<td><xsl:text>Jindabyne </xsl:text></td>
						<xsl:for-each select="forecast-period">
							<xsl:if test="number(@index) = 0">
								<!-- forecast -->
								<xsl:for-each select="text">
									<xsl:if test="@type='precis'">
										<td>
										<div class="smdPrecis">
											<xsl:value-of select="text()"/>
										</div>
										</td>
									</xsl:if>
								</xsl:for-each>
								<!-- min value -->
								<td></td>
								<xsl:for-each select="element">
									<xsl:if test="@type='air_temperature_minimum'">
										<td>
										<div class="min">
											<xsl:text>Min </xsl:text>
											<xsl:value-of select="text()"/>
										</div>
										</td>
									</xsl:if>
								</xsl:for-each>						
							</xsl:if>
						</xsl:for-each>
						<!-- get the MAX value last -->
						<xsl:for-each select="forecast-period">
							<xsl:if test="number(@index) = 0">
								<xsl:for-each select="element">
									<xsl:if test="@type='air_temperature_maximum'">
										<td>
										<div class="max">
											<xsl:text>Max </xsl:text>
											<xsl:value-of select="text()"/>
										</div>
										</td>
									</xsl:if>
								</xsl:for-each>
							</xsl:if>
						</xsl:for-each>
					</xsl:if>
				</xsl:for-each>
			</div>
			</tr>
				
			<!-- Perisher Valley 1 -->
			<tr>
			<div class="area">
				<xsl:for-each select="$data1/product/forecast/area">
					<xsl:if test="@description='Perisher Valley'">
						<td><xsl:text>Perisher Valley </xsl:text></td>
						<xsl:for-each select="forecast-period">
							<xsl:if test="number(@index) = 0">
								<!-- forecast -->
								<xsl:for-each select="text">
									<xsl:if test="@type='precis'">
										<td>
										<div class="smdPrecis">
											<xsl:value-of select="text()"/>
										</div>
										</td>
									</xsl:if>
								</xsl:for-each>
								<!-- min values -->
								<td></td>
								<xsl:for-each select="element">
									<xsl:if test="@type='air_temperature_minimum'">
										<td>
										<div class="min">
											<xsl:text>Min </xsl:text>
											<xsl:value-of select="text()"/>
										</div>
										</td>
									</xsl:if>
								</xsl:for-each>						
							</xsl:if>
						</xsl:for-each>
						<!-- get the MAX value last -->
						<xsl:for-each select="forecast-period">
							<xsl:if test="number(@index) = 0">
								<xsl:for-each select="element">
									<xsl:if test="@type='air_temperature_maximum'">
										<td>
										<div class="max">
											<xsl:text>Max </xsl:text>
											<xsl:value-of select="text()"/>
										</div>
										</td>
									</xsl:if>
								</xsl:for-each>
							</xsl:if>
						</xsl:for-each>
					</xsl:if>
				</xsl:for-each>
			</div>
			</tr>
				
			<!-- Thredbo Top Station 1 -->
			<tr>
			<div class="area">
				<xsl:for-each select="$data1/product/forecast/area">
					<xsl:if test="@description='Thredbo Top Station'">
						<td><xsl:text>Thredbo Top Station </xsl:text></td>
						<xsl:for-each select="forecast-period">
							<xsl:if test="number(@index) = 0">
								<!-- forecast -->
								<xsl:for-each select="text">
									<xsl:if test="@type='precis'">
										<td>
										<div class="smdPrecis">
											<xsl:value-of select="text()"/>
										</div>
										</td>
									</xsl:if>
								</xsl:for-each>
								<td></td>
								<!-- min values -->
								<xsl:for-each select="element">
									<xsl:if test="@type='air_temperature_minimum'">
										<td>
										<div class="min">
											<xsl:text>Min </xsl:text>
											<xsl:value-of select="text()"/>
										</div>
										</td>
									</xsl:if>
								</xsl:for-each>						
							</xsl:if>
						</xsl:for-each>
						<!-- get the MAX value last -->
						<xsl:for-each select="forecast-period">
							<xsl:if test="number(@index) = 0">
								<xsl:for-each select="element">
									<xsl:if test="@type='air_temperature_maximum'">
										<td>
										<div class="max">
											<xsl:text>Max </xsl:text>
											<xsl:value-of select="text()"/>
										</div>
										</td>
									</xsl:if>
								</xsl:for-each>
							</xsl:if>
						</xsl:for-each>
					</xsl:if>
				</xsl:for-each>
			</div>
			</tr>
				
			</table>
		</div><!-- Day 1 -->
		
		<div class="smdDay"><!-- Day 2 -->
			<!-- get date with formatting -->
			<div class="datetime">
				<xsl:variable name="issue-time" select="$data1/product/amoc/issue-time-local"/>
				<xsl:for-each select="$data1/product/forecast/area">
					<xsl:if test="@description='Jindabyne'">
						<xsl:for-each select="forecast-period">
							<xsl:if test="number(@index) = 1">
								<xsl:variable name="start-time" select="@start-time-local"/>
								
								<xsl:text>Forecast for </xsl:text>
								
								<xsl:if test="format-dateTime($issue-time, '[Y0001]-[M01]-[D01]')=format-dateTime($start-time, '[Y0001]-[M01]-[D01]')">
									<xsl:text>the rest of </xsl:text>
								</xsl:if>
								
								<xsl:value-of select="format-dateTime($start-time, '[FNn], [D1o] [MNn]')"/>
							</xsl:if>
						</xsl:for-each>
					</xsl:if>
				</xsl:for-each>
			</div>
			
			<table class="smdT">
			
			<!-- Jindabyne 2 -->
			<tr>
			<div class="area">
				<xsl:for-each select="$data1/product/forecast/area">
					<xsl:if test="@description='Jindabyne'">
						<td><xsl:text>Jindabyne </xsl:text></td>
						<xsl:for-each select="forecast-period">
							<xsl:if test="number(@index) = 1">
								<!-- forecast -->
								<xsl:for-each select="text">
									<xsl:if test="@type='precis'">
										<td>
										<div class="smdPrecis">
											<xsl:value-of select="text()"/>
										</div>
										</td>
									</xsl:if>
								</xsl:for-each>
								<!-- min values -->
								<xsl:for-each select="element">
									<xsl:if test="@type='air_temperature_minimum'">
										<td>
										<div class="min">
											<xsl:text>Min </xsl:text>
											<xsl:value-of select="text()"/>
										</div>
										</td>
									</xsl:if>
								</xsl:for-each>						
							</xsl:if>
						</xsl:for-each>
						<!-- get the MAX value last -->
						<xsl:for-each select="forecast-period">
							<xsl:if test="number(@index) = 1">
								<xsl:for-each select="element">
										<xsl:if test="@type='air_temperature_maximum'">
											<td>
											<div class="max">
												<xsl:text>Max </xsl:text>
												<xsl:value-of select="text()"/>
											</div>
											</td>
										</xsl:if>
									
								</xsl:for-each>
							</xsl:if>
						</xsl:for-each>
					</xsl:if>
				</xsl:for-each>
			</div>
			</tr>
			
			<!-- Perisher Valley 2 -->
			<tr>
			<div class="area">
				<xsl:for-each select="$data1/product/forecast/area">
					<xsl:if test="@description='Perisher Valley'">
						<td><xsl:text>Perisher Valley </xsl:text></td>
						<xsl:for-each select="forecast-period">
							<xsl:if test="number(@index) = 1">
								<!-- forecast -->
								<xsl:for-each select="text">
									<xsl:if test="@type='precis'">
										<td>
										<div class="smdPrecis">
											<xsl:value-of select="text()"/>
										</div>
										</td>
									</xsl:if>
								</xsl:for-each>
								<!-- min values -->
								<xsl:for-each select="element">
									<xsl:if test="@type='air_temperature_minimum'">
										<td>
										<div class="min">
											<xsl:text>Min </xsl:text>
											<xsl:value-of select="text()"/>
										</div>
										</td>
									</xsl:if>
								</xsl:for-each>						
							</xsl:if>
						</xsl:for-each>
						<!-- get the MAX value last -->
						<xsl:for-each select="forecast-period">
							<xsl:if test="number(@index) = 1">
								<xsl:for-each select="element">
									<xsl:if test="@type='air_temperature_maximum'">
										<td>
										<div class="max">
											<xsl:text>Max </xsl:text>
											<xsl:value-of select="text()"/>
										</div>
										</td>
									</xsl:if>
								</xsl:for-each>
							</xsl:if>
						</xsl:for-each>
					</xsl:if>
				</xsl:for-each>
			</div>
			</tr>
				
			<!-- Thredbo Top Station 2-->
			<tr>
			<div class="area">
				
				<xsl:for-each select="$data1/product/forecast/area">
					<xsl:if test="@description='Thredbo Top Station'">
						<td><xsl:text>Thredbo Top Station </xsl:text></td>
						<xsl:for-each select="forecast-period">
							<xsl:if test="number(@index) = 1">
								<!-- forecast -->
								<xsl:for-each select="text">
									<xsl:if test="@type='precis'">
										<td>
										<div class="smdPrecis">
											<xsl:value-of select="text()"/>
										</div>
										</td>
									</xsl:if>
								</xsl:for-each>
								<!-- min values -->
								<xsl:for-each select="element">
									<xsl:if test="@type='air_temperature_minimum'">
										<td>
										<div class="min">
											<xsl:text>Min </xsl:text>
											<xsl:value-of select="text()"/>
										</div>
										</td>
									</xsl:if>
								</xsl:for-each>						
							</xsl:if>
						</xsl:for-each>
						<!-- get the MAX value last -->
						<xsl:for-each select="forecast-period">
							<xsl:if test="number(@index) = 1">
								<xsl:for-each select="element">
									<xsl:if test="@type='air_temperature_maximum'">
										<td>
										<div class="max">
											<xsl:text>Max </xsl:text>
											<xsl:value-of select="text()"/>
										</div>
										</td>
									</xsl:if>
								</xsl:for-each>
							</xsl:if>
						</xsl:for-each>
					</xsl:if>
				</xsl:for-each>
			</div>
			</tr>
				
			</table>
		</div><!-- Day 2 -->
		
		<div class="smdDay"><!-- Day 3 -->
			<!-- get date with formatting -->
			<div class="datetime">
				<xsl:variable name="issue-time" select="$data1/product/amoc/issue-time-local"/>
				<xsl:for-each select="$data1/product/forecast/area">
					<xsl:if test="@description='Jindabyne'">
						<xsl:for-each select="forecast-period">
							<xsl:if test="number(@index) = 2">
								<xsl:variable name="start-time" select="@start-time-local"/>
								
								<xsl:text>Forecast for </xsl:text>
								
								<xsl:if test="format-dateTime($issue-time, '[Y0001]-[M01]-[D01]')=format-dateTime($start-time, '[Y0001]-[M01]-[D01]')">
									<xsl:text>the rest of </xsl:text>
								</xsl:if>
								
								<xsl:value-of select="format-dateTime($start-time, '[FNn], [D1o] [MNn]')"/>
							</xsl:if>
						</xsl:for-each>
					</xsl:if>
				</xsl:for-each>
			</div>
			
			<table class="smdT">
			<!-- Jindabyne 3 -->
			<tr>
			<div class="area">
				<xsl:for-each select="$data1/product/forecast/area">
					<xsl:if test="@description='Jindabyne'">
						<td><xsl:text>Jindabyne </xsl:text></td>
						<xsl:for-each select="forecast-period">
							<xsl:if test="number(@index) = 2">
								<!-- forecast -->
								<xsl:for-each select="text">
									<xsl:if test="@type='precis'">
										<td>
										<div class="smdPrecis">
											<xsl:value-of select="text()"/>
										</div>
										</td>
									</xsl:if>
								</xsl:for-each>
								<!-- min values -->
								<xsl:for-each select="element">
									<xsl:if test="@type='air_temperature_minimum'">
										<td>
										<div class="min">
											<xsl:text>Min </xsl:text>
											<xsl:value-of select="text()"/>
										</div>
										</td>
									</xsl:if>
								</xsl:for-each>						
							</xsl:if>
						</xsl:for-each>
						<!-- get the MAX value last -->
						<xsl:for-each select="forecast-period">
							<xsl:if test="number(@index) = 2">
								<xsl:for-each select="element">
									<xsl:if test="@type='air_temperature_maximum'">
										<td>
										<div class="max">
											<xsl:text>Max </xsl:text>
											<xsl:value-of select="text()"/>
										</div>
										</td>
									</xsl:if>
									
								</xsl:for-each>
							</xsl:if>
						</xsl:for-each>
					</xsl:if>
				</xsl:for-each>
			</div>
			</tr>
			
			<!-- Perisher Valley 3 -->
			<tr>
			<div class="area">
				<xsl:for-each select="$data1/product/forecast/area">
					<xsl:if test="@description='Perisher Valley'">
						<td><xsl:text>Perisher Valley </xsl:text></td>
						<xsl:for-each select="forecast-period">
							<xsl:if test="number(@index) = 2">
								<!-- forecast -->
								<xsl:for-each select="text">
									<xsl:if test="@type='precis'">
										<td>
										<div class="smdPrecis">
											<xsl:value-of select="text()"/>
										</div>
										</td>
									</xsl:if>
								</xsl:for-each>
								<!-- min values -->
								<xsl:for-each select="element">
									<xsl:if test="@type='air_temperature_minimum'">
										<td>
										<div class="min">
											<xsl:text>Min </xsl:text>
											<xsl:value-of select="text()"/>
										</div>
										</td>
									</xsl:if>
								</xsl:for-each>						
							</xsl:if>
						</xsl:for-each>
						<!-- get the MAX value last -->
						<xsl:for-each select="forecast-period">
							<xsl:if test="number(@index) = 2">
								<xsl:for-each select="element">
									<xsl:if test="@type='air_temperature_maximum'">
										<td>
										<div class="max">
											<xsl:text>Max </xsl:text>
											<xsl:value-of select="text()"/>
										</div>
										</td>
									</xsl:if>
									
								</xsl:for-each>
							</xsl:if>
						</xsl:for-each>
					</xsl:if>
				</xsl:for-each>
			</div>
			</tr>
				
			<!-- Thredbo Top Station 3-->
			<tr>
			<div class="area">
				<xsl:for-each select="$data1/product/forecast/area">
					<xsl:if test="@description='Thredbo Top Station'">
						<td><xsl:text>Thredbo Top Station </xsl:text></td>
						<xsl:for-each select="forecast-period">
							<xsl:if test="number(@index) = 2">
								<!-- forecast -->
								<xsl:for-each select="text">
									<xsl:if test="@type='precis'">
										<td>
										<div class="smdPrecis">
											<xsl:value-of select="text()"/>
										</div>
										</td>
									</xsl:if>
								</xsl:for-each>
								<!-- min values -->
								<xsl:for-each select="element">
									<xsl:if test="@type='air_temperature_minimum'">
										<td>
										<div class="min">
											<xsl:text>Min </xsl:text>
											<xsl:value-of select="text()"/>
										</div>
										</td>
									</xsl:if>
								</xsl:for-each>						
							</xsl:if>
						</xsl:for-each>
						<!-- get the MAX value last -->
						<xsl:for-each select="forecast-period">
							<xsl:if test="number(@index) = 2">
								<xsl:for-each select="element">
									<xsl:if test="@type='air_temperature_maximum'">
										<td>
										<div class="max">
											<xsl:text>Max </xsl:text>
											<xsl:value-of select="text()"/>
										</div>
										</td>
									</xsl:if>
									
								</xsl:for-each>
							</xsl:if>
						</xsl:for-each>
					</xsl:if>
				</xsl:for-each>
			</div>
			</tr>
				
			</table>
		
		</div><!-- Day 3 -->
		
	</div><!-- Snowy Mountain District Forecast -->
</body>
</html>
</xsl:template>


</xsl:stylesheet>