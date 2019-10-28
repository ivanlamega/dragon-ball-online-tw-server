CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1463;
	title = 146302;

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
				conv = 146309;
				ctype = 1;
				idx = 4372101;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 146308;
				gtype = 1;
				area = 146301;
				goal = 146304;
				grade = 132203;
				rwd = 100;
				sort = 146305;
				stype = 2;
				taid = 1;
				title = 146302;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 146308;
			gtype = 1;
			oklnk = 2;
			area = 146301;
			goal = 146304;
			sort = 146305;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 146302;
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
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 146314;
			nextlnk = 254;
			rwdtbl = 146301;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 1351108;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 146307;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 4372101;
			}
			CDboTSCheckLvl
			{
				maxlvl = 55;
				minlvl = 47;
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

