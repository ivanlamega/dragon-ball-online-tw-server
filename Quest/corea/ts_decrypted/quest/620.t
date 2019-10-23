CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 620;
	title = 62002;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGCond
		{
			cid = 3;
			prelnk = "2;";
			nolnk = 255;
			rm = 0;
			yeslnk = 4;

			CDboTSClickNPC
			{
				npcidx = 4751107;
			}
		}
		CDboTSContGAct
		{
			cid = 4;
			elnk = 255;
			nextlnk = 100;
			prelnk = "3;";

			CDboTSActPortal
			{
				dx = "0.000000";
				px = "5886.000000";
				widx = 1;
				dy = "0.000000";
				py = "0.000000";
				taid = 1;
				type = 0;
				dz = "0.000000";
				pz = "545.000000";
			}
		}
		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 3;
			prelnk = "1;";

			CDboTSActRegQInfo
			{
				cont = 62008;
				gtype = 1;
				area = 62001;
				goal = 62004;
				grade = 132203;
				rwd = 100;
				sort = 62005;
				stype = 2;
				taid = 1;
				title = 62002;
			}
			CDboTSActNPCConv
			{
				conv = 62009;
				ctype = 1;
				idx = 4751107;
				taid = 2;
			}
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;1;252;";
			type = 0;
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "100;";
			type = 1;
		}
		CDboTSContGAct
		{
			cid = 252;
			elnk = 255;
			nextlnk = 253;
			prelnk = "2;";
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 62008;
			gtype = 1;
			oklnk = 2;
			area = 62001;
			goal = 62004;
			sort = 62005;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 62002;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 62014;
			nextlnk = 254;
			rwdtbl = 62001;
			rwdtype = 0;
			ltime = -1;
			prelnk = "4;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 4751104;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 62007;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckPCRace
			{
				raceflg = 2;
			}
			CDboTSCheckLvl
			{
				maxlvl = 29;
				minlvl = 21;
			}
			CDboTSCheckClrQst
			{
				and = "619;";
			}
			CDboTSClickNPC
			{
				npcidx = 4751107;
			}
		}
	}
}

