CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 189;
	title = 18902;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGCond
		{
			cid = 3;
			prelnk = "2;";
			nolnk = 255;
			rm = 0;
			yeslnk = 100;

			CDboTSBindStone
			{
			}
		}
		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 3;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 18909;
				ctype = 1;
				idx = 4181101;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 18908;
				gtype = 1;
				area = 18901;
				goal = 18904;
				m0fz = "4054.909912";
				m0widx = 1;
				sort = 18905;
				stype = 2;
				m0fy = "-43.786999";
				grade = 132203;
				m0fx = "4568.749023";
				m0ttip = 18915;
				rwd = 100;
				taid = 1;
				title = 18902;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 18907;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 4181101;
			}
			CDboTSCheckLvl
			{
				maxlvl = 10;
				minlvl = 2;
			}
			CDboTSCheckPCRace
			{
				raceflg = 1;
			}
			CDboTSCheckClrQst
			{
				and = "3;";
			}
		}
		CDboTSContGAct
		{
			cid = 252;
			elnk = 255;
			nextlnk = 253;
			prelnk = "2;";
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;1;252;";
			type = 0;
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 18908;
			gtype = 1;
			oklnk = 2;
			area = 18901;
			goal = 18904;
			sort = 18905;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 18902;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 18914;
			nextlnk = 254;
			rwdtbl = 18901;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 4181101;
			}
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "100;";
			type = 1;
		}
	}
}

