CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 323;
	title = 32302;

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
				conv = 32309;
				ctype = 1;
				idx = 4511602;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 32308;
				gtype = 1;
				area = 32301;
				goal = 32304;
				grade = 132203;
				rwd = 100;
				sort = 32305;
				stype = 2;
				taid = 1;
				title = 32302;
			}
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "100;";
			type = 1;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 32314;
			nextlnk = 254;
			rwdtbl = 32301;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 4651206;
			}
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
			cont = 32308;
			gtype = 1;
			oklnk = 2;
			area = 32301;
			goal = 32304;
			sort = 32305;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 32302;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 32307;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 4511602;
			}
			CDboTSCheckPCRace
			{
				raceflg = 2;
			}
			CDboTSCheckLvl
			{
				maxlvl = 25;
				minlvl = 17;
			}
			CDboTSCheckClrQst
			{
				and = "286;";
			}
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

