CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 223;
	title = 22302;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 100;
			prelnk = "1;";

			CDboTSActRegQInfo
			{
				cont = 22308;
				gtype = 1;
				area = 22301;
				goal = 22304;
				grade = 132203;
				rwd = 100;
				sort = 22305;
				stype = 2;
				taid = 1;
				title = 22302;
			}
			CDboTSActNPCConv
			{
				conv = 22309;
				ctype = 1;
				idx = 4511510;
				taid = 2;
			}
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
			cont = 22308;
			gtype = 1;
			oklnk = 2;
			area = 22301;
			goal = 22304;
			sort = 22305;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 22302;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 22314;
			nextlnk = 254;
			rwdtbl = 22301;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 3142210;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 22307;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 4511510;
			}
			CDboTSCheckPCRace
			{
				raceflg = 2;
			}
			CDboTSCheckLvl
			{
				maxlvl = 13;
				minlvl = 5;
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
	}
}

