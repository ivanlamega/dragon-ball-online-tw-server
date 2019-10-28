CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 544;
	title = 54402;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 100;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 54409;
				ctype = 1;
				idx = 1651104;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 54408;
				gtype = 0;
				area = 54401;
				goal = 54404;
				grade = 132203;
				rwd = 100;
				sort = 54405;
				stype = 1;
				taid = 1;
				title = 54402;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 54414;
			nextlnk = 254;
			rwdtbl = 54401;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 3142109;
			}
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
			cont = 54408;
			gtype = 0;
			oklnk = 2;
			area = 54401;
			goal = 54404;
			sort = 54405;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 54402;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 54407;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckPCRace
			{
				raceflg = 4;
			}
			CDboTSClickNPC
			{
				npcidx = 1651104;
			}
			CDboTSCheckLvl
			{
				maxlvl = 27;
				minlvl = 19;
			}
			CDboTSCheckClrQst
			{
				and = "514;";
			}
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;1;252;";
			type = 0;
		}
	}
}

