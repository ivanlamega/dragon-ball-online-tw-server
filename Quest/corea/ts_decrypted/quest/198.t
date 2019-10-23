CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 198;
	title = 19802;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 3;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 19809;
				ctype = 1;
				idx = 8512101;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 19808;
				gtype = 0;
				area = 19801;
				goal = 19804;
				grade = 132203;
				rwd = 100;
				sort = 19805;
				stype = 1;
				taid = 1;
				title = 19802;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 19814;
			nextlnk = 254;
			rwdtbl = 19801;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 8512101;
			}
		}
		CDboTSContGCond
		{
			cid = 3;
			prelnk = "2;";
			nolnk = 255;
			rm = 0;
			yeslnk = 100;

			CDboTSTeleport
			{
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 19807;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckPCRace
			{
				raceflg = 1;
			}
			CDboTSClickNPC
			{
				npcidx = 8512101;
			}
			CDboTSCheckLvl
			{
				maxlvl = 15;
				minlvl = 2;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 19808;
			gtype = 0;
			oklnk = 2;
			area = 19801;
			goal = 19804;
			sort = 19805;
			prelnk = "0;";
			ds = 1;
			grade = 0;
			rwd = 100;
			title = 19802;
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "1;0;252;";
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
	}
}

